#ifndef __LRUSC_H_INCLUDED__
#define __LRUSC_H_INCLUDED__
#include<iostream>
#include<vector>
#include<string>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

class lrusc {
public:
	lrusc();
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
	vector<int> frame;
    vector<int> rbit;
};


lrusc::lrusc() {
	srand(time(NULL));
	times = 100000;
	page_fault1 = vector<int>(10, 0);
	page_fault2 = vector<int>(10, 0);

}

void lrusc::random_string1() {
	reference_string.resize(times);
	ifstream input("random_string.txt");

	for (int i = 0; i < times; i++)
		input >> reference_string[i];	

	input.close();

}
void lrusc::locality_string2() {
	reference_string.resize(times);
	ifstream input("locality_string.txt");

	for (int i = 0; i < times; i++)
		input >> reference_string[i];

	input.close();
}last

int lrusc::already_in_frame(int page) {
	for (int i = 0; i < frame.size(); i++)
		if (page == frame[i])
			return i;
		
	return -1;
}
void lrusc::change_victim_page(int page) {
	for(int i=0;i<frame.size();i=(i+1)%frame.size()){
		if(rbit[i]==0){
				frame.erase(frame.begin()+i);
				rbit.erase(rbit.begin()+i);
				frame.push_back(page);
				rbit.push_back(0);
				break;
		}
		else
				rbit[i]=0;
	}
}

void lrusc::run()
{
	int tmp;
	ofstream rand_file("random_result/lrusc_rand.txt");
	ofstream locality_file("locality_result/lrusc_locality.txt");
	
	//run each 
	for (int k = 0; k < 2; k++)
	{
		//input random,locality,
		switch (k) {
		case 0:
			random_string1();
			cout << "Random string:" << endl;

			break;
		case 1:
			cout << "Locality string:" << endl;
			locality_string2();
			
		}
		//run 10,20,30........,100 frames
		for (int i = 0; i < 10; i++) {
            
            num_frame = 10 * (i + 1);

			if(k==0)
				rand_file<<num_frame<<" ";
			else if(k==1)
				locality_file<<num_frame<<" ";

			frame.resize(0);
			rbit.resize(0);
			//input page
			for (int j = 0; j < times; j++) {
				//check whether page already in frame
				if ((tmp=already_in_frame(reference_string[j]))==-1) {

					//check whether frames are filled
					if (frame.size() == num_frame)
						change_victim_page(reference_string[j]);
					else {
						frame.push_back(reference_string[j]);
						rbit.push_back(0);
					}
					//increase page fault
					switch (k) {
					case 0:
						page_fault1[i]++;
						break;
					case 1:
						page_fault2[i]++;
					}

				}			
				else{
						frame.erase(frame.begin()+tmp);
						frame.push_back(reference_string[j]);
						rbit.erase(rbit.begin()+tmp);
						rbit.push_back(1);
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