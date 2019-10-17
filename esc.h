#ifndef __ESC_H_INCLUDED__
#define __ESC_H_INCLUDED__
#include<iostream>
#include<vector>
#include<string>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

class esc {
public:
	esc();
	void run();

private:
	void random_string1();
	void locality_string2();
	void bubble_sort_string3();
	int already_in_frame(int);
	void change_victim_page(int);
private:
	int num_frame;
	vector<int> reference_string;
	int times;
	vector<int> page_fault1;
	vector<int> page_fault2;
	vector<int> page_fault3;
	vector<int>frame;
	vector<int>rbit;
	vector<int>dbit;
};


esc::esc() {
	srand(time(NULL));
	num_frame = 10;
	times = 100000;
	page_fault1 = vector<int>(10, 0);
	page_fault2 = vector<int>(10, 0);
	page_fault3 = vector<int>(10, 0);
}
void esc::random_string1() {
	reference_string.resize(times);

	ifstream input("random_string.txt");
	for (int i = 0; i < times; i++)
		input >> reference_string[i];

	input.close();
}
void esc::locality_string2() {
	reference_string.resize(times);
	ifstream input("locality_string.txt");

	for (int i = 0; i < times; i++)
		input >> reference_string[i];

	input.close();
}

void esc::bubble_sort_string3() {
	reference_string.resize(times);
	ifstream input("bubble_sort_string.txt");

	for (int i = 0; i < times; i++)
		input >> reference_string[i];
	input.close();
}

int esc::already_in_frame(int page) {
	for (int i = 0; i < frame.size(); i++)
		if (page == frame[i])
			return i;

	return -1;
}
void esc::change_victim_page(int page) {
	double update_pro=0.5;
	bool flag=false;
	//vector<int> rbitdbit[4];
	/*
	for (int i = 0; i < frame.size(); i++){
		if (rbit[i] == 0 && dbit[i] == 0)
			rbitdbit[0].push_back(i);
		else if (rbit[i] == 0 && dbit[i] == 1)
			rbitdbit[1].push_back(i);
		else if (rbit[i] == 1 && dbit[i] == 0)
			rbitdbit[2].push_back(i);
		else		
			rbitdbit[3].push_back(i);
	}
	*/
	for(int i=0;i<2;i++){
		for(int j=0;j<frame.size();j++)
			if(rbit[j]==0&&dbit[j]==0){
				rbit.erase(rbit.begin()+j);
				dbit.erase(dbit.begin()+j);
				frame.erase(frame.begin()+j);
				frame.push_back(page);
				rbit.push_back(1);
				double r=(double)rand()/RAND_MAX;
				if(r<update_pro)
					dbit.push_back(1);
				else
					dbit.push_back(0);
				flag = ~flag;
				break;
			}

		if(flag)
			break;
		for (int j = 0; j < frame.size(); j++)
			if(rbit[j]==0&&dbit[j]==1){
				rbit.erase(rbit.begin()+j);
				dbit.erase(dbit.begin()+j);
				frame.erase(frame.begin()+j);
				frame.push_back(page);
				rbit.push_back(1);
				double r=(double)rand()/RAND_MAX;
				if(r<update_pro)
					dbit.push_back(1);
				else
					dbit.push_back(0);
				flag = ~flag;
				break;
			}
			else
				rbit[j]=0;
		if(flag)
			break;
	}
	
}

void esc::run()
{
	double update_pro=0.5;
	int tmp;
	ofstream rand_file("random_result/esc_rand.txt");
	ofstream locality_file("locality_result/esc_locality.txt");
	ofstream bubble_sort_file("bubble_sort_result/esc_bubble_sort.txt");
	for (int k = 0; k < 3; k++) {
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
			cout<<"Bubble sort string:"<<endl;
			bubble_sort_string3();
			
	
		}

		for (int i = 0; i < 10; i++) {
			num_frame = 10 * (i + 1);
			
			//write file
			if(k==0)
				rand_file<<num_frame<<" ";
			else if(k==1)
				locality_file<<num_frame<<" ";
			else
				bubble_sort_file<<num_frame<<" ";

			
			
			frame.clear();
			for (int j = 0; j < times; j++) {
				
				if ((tmp = already_in_frame(reference_string[j])) == -1) {

					
					if (frame.size() == num_frame)
						change_victim_page(reference_string[j]);
					else
					{
						frame.push_back(reference_string[j]);
						rbit.push_back(1);
						double r = (double)rand() / RAND_MAX;
						if (r < update_pro)
							dbit.push_back(1);
						else
							dbit.push_back(0);
					}

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
				else{
					rbit[tmp] = 1;
					double r = (float)rand() / RAND_MAX;
					if (r < update_pro)
						dbit[tmp]=1;
					else
						dbit[tmp]=0;
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