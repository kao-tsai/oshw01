#ifndef __OP_H_INCLUDED__
#define __OP_H_INCLUDED__
#include<iostream>
#include<vector>
#include<string>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

class op {
public:
	op();
	void run();

private:
	void random_string1();
	void locality_string2();
	int already_in_frame(int);
	void change_victim_page(int, int);
	int update_next_time(int, int);
private:
	int num_frame;
	vector<int> reference_string;
	int times;
	vector<int> page_fault1;
	vector<int> page_fault2;
	vector<int> frame;
	vector<int>next_time;
};


op::op() {
	srand(time(NULL));
	num_frame = 10;
	times = 100000;
	page_fault1 = vector<int>(10, 0);
	page_fault2 = vector<int>(10, 0);

}

void op::random_string1() {
	reference_string.resize(times);
	ifstream input("random_string.txt");

	for (int i = 0; i < times; i++)
		input >> reference_string[i];	

	input.close();

}
void op::locality_string2() {
	reference_string.resize(times);
	ifstream input("locality_string.txt");

	for (int i = 0; i < times; i++)
		input >> reference_string[i];

	input.close();
}

int op::already_in_frame(int page) {
	for (int i = 0; i < frame.size(); i++)
		if (page == frame[i])
			return i;
		
	return -1;
}
int op::update_next_time(int page,int next) {
	int next_position=times-1;
	for (int i = next + 1; i < times; i++)
	{
		if (reference_string[i] == page)
		{
			next_position = i;
			break;
		}
		if (i == times - 1)
		{
			next_position = times;
			break;
		}
	}


	return next_position;
}
void op::change_victim_page(int page,int next) {
	int max = 0, victim_position,tmp;
	for (int i = 0; i < next_time.size(); i++)
	{
		if (next_time[i] > max)
		{
			max = next_time[i];
			victim_position = i;
		}
	}
	frame[victim_position] = page;
	tmp=update_next_time(page,next);
	next_time[victim_position] = tmp;
}

void op::run()
{
	int count = 0, tmp,next;
	ofstream rand_file("random_result/opt_rand.txt");
	ofstream locality_file("locality_result/opt_locality.txt");
	
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
			next_time.resize(0);
			//input page
			for (int j = 0; j < times; j++) {
				//check whether page already in frame
				if ((tmp=already_in_frame(reference_string[j]))==-1) {

					//check whether frames are filled
					if (frame.size() == num_frame)
						change_victim_page(reference_string[j], j);
					else {
						frame.push_back(reference_string[j]);
						next=update_next_time(reference_string[j],j);
						next_time.push_back(next);
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
					next = update_next_time(reference_string[j], j);
					next_time[tmp] = next;
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