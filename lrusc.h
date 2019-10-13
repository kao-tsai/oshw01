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
	void change_victim_page(int,int);
private:
	int num_frame;
	vector<int> reference_string;
	int times;
	vector<int> page_fault1;
	vector<int> page_fault2;
	vector<int> frame;
	vector<int> last_time;
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
}

int lrusc::already_in_frame(int page) {
	for (int i = 0; i < frame.size(); i++)
		if (page == frame[i])
			return i;
		
	return -1;
}
void lrusc::change_victim_page(int page,int last) {
	int min = last_time[0], victim_position=0;
	for (int i = 0; i < last_time.size(); i++)
	{
		if (last_time[i] < min)
		{
			min = last_time[i];
			victim_position = i;
		}
	}
	frame[victim_position] = page;

	last_time[victim_position] = last;
}

void lrusc::run()
{
	int tmp;
	ofstream rand_file("lrusc_rand.txt");
	ofstream locality_file("lrusc_locality.txt");
	
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
			last_time.resize(0);
			//input page
			for (int j = 0; j < times; j++) {
				//check whether page already in frame
				if ((tmp=already_in_frame(reference_string[j]))==-1) {

					//check whether frames are filled
					if (frame.size() == num_frame)
						change_victim_page(reference_string[j], j);
					else {
						frame.push_back(reference_string[j]);
						last_time.push_back(j);
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
				else
					last_time[tmp] = j;			
				
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