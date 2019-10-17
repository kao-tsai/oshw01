#ifndef __FIFO_H_INCLUDED__
#define __FIFO_H_INCLUDED__
#include<iostream>
#include<vector>
#include<string>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

class FIFO {
public:
	FIFO();
	void run();

private:
	void random_string1();
	void locality_string2();
	void bubble_sort_string3();
	bool already_in_frame(int);
	void change_victim_page(int);
private:
	int num_frame;
	vector<int> reference_string;
	int times;
	vector<int> page_fault1;
	vector<int> page_fault2;
	vector<int> page_fault3;
	vector<int> interrupt;
	vector<int> diskIO;
	vector<int>frame;
};


FIFO::FIFO() {
	srand(time(NULL));
	times = 100000;
	page_fault1 = vector<int>(10, 0);
	page_fault2 = vector<int>(10, 0);
	page_fault3 = vector<int>(10, 0);
	interrupt=vector<int>(10,0);
	diskIO=vector<int>(10,0);
}
void FIFO::random_string1() {
	reference_string.resize(times);

	ifstream input("random_string.txt");
	for (int i = 0; i < times; i++)
		input >> reference_string[i];
	
	input.close();
}
void FIFO::locality_string2() {
	reference_string.resize(times);
	ifstream input("locality_string.txt");

	for (int i = 0; i < times; i++)
		input >> reference_string[i];

	input.close();
}
void FIFO::bubble_sort_string3() {
	reference_string.resize(times);
	ifstream input("bubble_sort_string.txt");

	for (int i = 0; i < times; i++)
		input >> reference_string[i];

	input.close();
}


bool FIFO::already_in_frame(int page) {
	for (int i = 0; i < frame.size(); i++)
		if (page == frame[i])
			return true;
		
	return false;
}

void FIFO::run()
{
	ofstream rand_file("random_result/fifo_rand.txt");
	ofstream locality_file("locality_result/fifo_locality.txt");
	ofstream bubble_sort_file("bubble_sort_result/fifo_bubble_sort.txt");
	for (int k = 0; k < 3; k++){
		switch (k) {
			case 0:
				cout << "Random string:" << endl;
				random_string1();
				break;

			case 1:
				cout << "Locality string:" << endl;
				locality_string2();
				break;
			case 2:
				cout << "Bubble sort string:"<<endl;
				bubble_sort_string3();
				
		}

		interrupt=vector<int>(10,0);
		diskIO=vector<int>(10,0);
		
		for (int i = 0; i < 10; i++) {
			num_frame = 10 * (i + 1);

			if(k==0)
				rand_file<<num_frame<<" ";
			else if(k==1)
				locality_file<<num_frame<<" ";
			else
				bubble_sort_file<<num_frame<<" ";
				
			frame.clear();
			for (int j = 0; j < times; j++) {

				if (!already_in_frame(reference_string[j])) {

					frame.push_back(reference_string[j]);
					if (frame.size() > num_frame)
						frame.erase(frame.begin());

					switch (k) {
						case 0:
							page_fault1[i]++;
							break;
						case 1:
							page_fault2[i]++;
							break;
						case 2:
							page_fault3[i]++;
					}

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
				break;
			case 2:
				cout << "Frame size:" << num_frame << ": " << page_fault3[i] << endl;
				bubble_sort_file<<page_fault3[i]<<endl;
			}
		}
	}

rand_file.close();
locality_file.close();
bubble_sort_file.close();
}
#endif
