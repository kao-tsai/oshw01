#ifndef __SC_H_INCLUDED__
#define __SC_H_INCLUDED__
#include<iostream>
#include<vector>
#include<string>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

class sc {
public:
	sc();
	void run();

private:
	void random_string1();
	void locality_string2();
	int already_in_frame(int);
	void change_victim_page(int);
private:
	int num_frame;
	vector<int> reference_string;
	int times;
	vector<int> page_fault1;
	vector<int> page_fault2;
	vector<int>frame;
    vector<int> rbit;
};


sc::sc() {
	srand(time(NULL));
	times = 100000;
	page_fault1 = vector<int>(10, 0);
	page_fault2 = vector<int>(10, 0);
}
void sc::random_string1() {
	reference_string.resize(times);

	ifstream input("random_string.txt");
	for (int i = 0; i < times; i++)
		input >> reference_string[i];
	
	input.close();
}
void sc::locality_string2() {
	reference_string.resize(times);
	ifstream input("locality_string.txt");

	for (int i = 0; i < times; i++)
		input >> reference_string[i];

	input.close();
}

int sc::already_in_frame(int page) {
	for (int i = 0; i < frame.size(); i++)
		if (page == frame[i])
			return i;
    return -1;
}
void sc::change_victim_page(int page){
    for (int i = 0; i < frame.size(); i=(i+1)%frame.size())
        if(rbit[i]==0){
            frame.erase(frame.begin() + i);
            rbit.erase(rbit.begin() + i);
            frame.push_back(page);
            rbit.push_back(0);
            break;
        }
        else
            rbit[i] = 0;
}

void sc::run()
{
    int tmp;
    ofstream rand_file("sc_rand.txt");
	ofstream locality_file("sc_locality.txt");
	for (int k = 0; k < 2; k++){
		switch (k) {
			case 0:
				cout << "Random string:" << endl;
				random_string1();
				
				break;
			case 1:
				cout << "Locality string:" << endl;
				locality_string2();
				
		}

		for (int i = 0; i < 10; i++) {
			num_frame = 10 * (i + 1);

			if(k==0)
				rand_file<<num_frame<<" ";
			else if(k==1)
				locality_file<<num_frame<<" ";

			frame.clear();
            rbit.clear();
            for (int j = 0; j < times; j++) {
                tmp=already_in_frame(reference_string[j]);
    
                if (tmp==-1) {
                    
                    if (frame.size() == num_frame)
						change_victim_page(reference_string[j]);
					else {
						frame.push_back(reference_string[j]);
						rbit.push_back(0);
					}

					switch (k) {
						case 0:
							page_fault1[i]++;
							break;
						case 1:
							page_fault2[i]++;

					}

				}
                else{
                    rbit[tmp] = 1;
                }
			}
			switch (k) {
			case 0:
				cout << "Frame size:" << num_frame << ": " << page_fault1[i] << endl;
				rand_file<<page_fault1[i]<<endl;
				break;
			case 1:
				cout << "Frame size:" << num_frame << ": " << page_fault2[i] << endl;
				locality_file<<page_fault2[i]<<endl;
			}
		}
	}

rand_file.close();
locality_file.close();
}
#endif
