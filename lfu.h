#ifndef __LFU_H_INCLUDED__
#define __LFU_H_INCLUDED__
#include<iostream>
#include<vector>
#include<string>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

class lfu {
public:
	lfu();
	void run();

private:
	void random_string1();
	void locality_string2();
	int already_in_frame(int);
	void change_victim_page(int);
	void aging();

private:
	int num_frame;
	vector<int> reference_string;
	int times;
	vector<int> page_fault1;
	vector<int> page_fault2;
	vector<int> frame;
	vector<int> count;
};


lfu::lfu() {
	srand(time(NULL));
	num_frame = 10;
	times = 100000;
	page_fault1 = vector<int>(10, 0);
	page_fault2 = vector<int>(10, 0);

}

void lfu::random_string1() {
	reference_string.resize(times);
	ifstream input("random_string.txt");

	for (int i = 0; i < times; i++)
		input >> reference_string[i];	

	input.close();

}
void lfu::locality_string2() {
	reference_string.resize(times);
	ifstream input("locality_string.txt");

	for (int i = 0; i < times; i++)
		input >> reference_string[i];

	input.close();
}

int lfu::already_in_frame(int page) {
	for (int i = 0; i < frame.size(); i++)
		if (page == frame[i])
			return i;
		
	return -1;
}

void lfu::aging(){
	for (int i = 0; i < count.size();i++)
		count[i]=count[i] /4;
}
void lfu::change_victim_page(int page) {
	int min = count[0], victim_position=0;
	for (int i = 0; i < count.size(); i++)
	{
		if (count[i] <min)
		{
			min = count[i];
			victim_position = i;
		}
	}
	frame.erase(frame.begin()+victim_position);
	count.erase(count.begin()+victim_position);
	frame.push_back(page);
	count.push_back(0);
}

void lfu::run()
{
	int tmp;
	ofstream rand_file("lfu_rand.txt");
	ofstream locality_file("lfu_locality.txt");
	
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
			count.resize(0);
			//input page
			for (int j = 0; j < times; j++) {
				//check whether page already in frame
				if ((tmp=already_in_frame(reference_string[j]))==-1) {

					//check whether frames are filled
					if (frame.size() == num_frame)
						change_victim_page(reference_string[j]);
					else {
						frame.push_back(reference_string[j]);
						count.push_back(0);
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
                    count[tmp]++;
                    
                if(j%100==0)
					aging();
				
				
				
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