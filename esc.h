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
	void my_ref_string3();
	int already_in_frame(int);
	void change_victim_page(int,int);
private:
	int num_frame;
	vector<int> reference_string;
	int times;
	vector<int> page_fault;
	vector<int> interrupt;
	vector<int>diskIO;
	vector<int>frame;
	vector<int>rbit;
	vector<int>dbit;
};


esc::esc() {
	srand(time(NULL));
	num_frame = 10;
	times = 100000;
	page_fault = vector<int>(10, 0);
	interrupt = vector<int>(10, 0);
	diskIO = vector<int>(10, 0);
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

void esc::my_ref_string3() {
	reference_string.resize(times);
	ifstream input("my_ref_string.txt");

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
void esc::change_victim_page(int page,int current_frame_num) {
	double update_pro=0.3;
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
		{
			diskIO[current_frame_num]++;
			break;
		}
	}
	
}

void esc::run()
{
	double update_pro=0.3;
	int tmp;

	ofstream rand_file("plot/random_result/esc_rand.txt");
	ofstream locality_file("plot/locality_result/esc_locality.txt");
	ofstream my_ref_file("plot/my_ref_result/esc_my_ref.txt");

	ofstream rand_int_file("plot/random_int_result/esc_int_rand.txt");
	ofstream locality_int_file("plot/locality_int_result/esc_int_locality.txt");
	ofstream my_ref_int_file("plot/my_ref_int_result/esc_int_my_ref.txt");

	ofstream rand_dis_file("plot/random_dis_result/esc_dis_rand.txt");
	ofstream locality_dis_file("plot/locality_dis_result/esc_dis_locality.txt");
	ofstream my_ref_dis_file("plot/my_ref_dis_result/esc_dis_my_ref.txt");

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
			my_ref_string3();
	
		}

		page_fault = vector<int>(10, 0);
		interrupt = vector<int>(10, 0);
		diskIO = vector<int>(10, 0);

		for (int i = 0; i < 10; i++) {
			num_frame = 10 * (i + 1);
			
			//write file
			switch(k){
				case 0:
					rand_file<<num_frame<<" ";
					rand_int_file<<num_frame<<" ";
					rand_dis_file<<num_frame<<" ";
					break;
				case 1:
					locality_file<<num_frame<<" ";
					locality_int_file<<num_frame<<" ";
					locality_dis_file<<num_frame<<" ";
					break;
				case 2:
					my_ref_file<<num_frame<<" ";
					my_ref_int_file<<num_frame<<" ";
					my_ref_dis_file<<num_frame<<" ";
			}
			frame.clear();
			rbit.clear();
			dbit.clear();
			for (int j = 0; j < times; j++) {
				
				if ((tmp = already_in_frame(reference_string[j])) == -1) {

					
					if (frame.size() == num_frame)
						change_victim_page(reference_string[j],i);
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

							page_fault[i]++;
							
				}
				else{
					rbit[tmp] = 1;
					double r = (double)rand() / RAND_MAX;
					if (r < update_pro)
						dbit[tmp]=1;
					
				}
			}

			interrupt[i]=page_fault[i]+diskIO[i];
			cout << "Frame size:" << num_frame << ": " << page_fault[i] << endl;

			switch (k) {
			case 0:
				rand_file<<page_fault[i]<<endl;
				rand_int_file<<interrupt[i]<<endl;
				rand_dis_file<<diskIO[i]<<endl;
				break;

			case 1:
				locality_file<<page_fault[i]<<endl;
				locality_int_file<<interrupt[i]<<endl;
				locality_dis_file<<diskIO[i]<<endl;
				break;

			case 2:
				my_ref_file<<page_fault[i]<<endl;
				my_ref_int_file<<interrupt[i]<<endl;
				my_ref_dis_file<<diskIO[i]<<endl;

			}
		}
	}
rand_file.close();
locality_file.close();
my_ref_file.close();
rand_int_file.close();
locality_int_file.close();
my_ref_int_file.close();
rand_dis_file.close();
locality_dis_file.close();
my_ref_dis_file.close();
}
#endif