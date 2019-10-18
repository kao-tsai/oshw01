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
	void my_ref_string3();
	int already_in_frame(int);
	void change_victim_page(int, int,int);
	int update_next_time(int, int);
private:
	int num_frame;
	vector<int> reference_string;
	int times;
	double update_pro;
	vector<int> page_fault;
	vector<int> interrupt;
	vector<int> diskIO;
	vector<int> frame;
	vector<int>next_time;
	vector<int>dbit;
};


op::op() {
	srand(time(NULL));
	num_frame = 10;
	times = 100000;
	page_fault = vector<int>(10, 0);
	interrupt=vector<int>(10,0);
	diskIO=vector<int>(10,0);
	dbit=vector<int>(10,0);
	update_pro=0.3;
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
void op::my_ref_string3() {
	reference_string.resize(times);
	ifstream input("my_ref_string.txt");

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
	for (int i = next + 1; i < times; i++){
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

void op::change_victim_page(int page,int next,int current_frame_num) {
	int max = 0, victim_position,tmp;
	for (int i = 0; i < next_time.size(); i++)
		if (next_time[i] > max){
			max = next_time[i];
			victim_position = i;
		}
	
	frame[victim_position] = page;
	tmp=update_next_time(page,next);
	next_time[victim_position] = tmp;
	if(dbit[victim_position]==1)
		diskIO[current_frame_num]++;
	double r=(double)rand()/RAND_MAX;
	if(r<update_pro)
		dbit[victim_position]=1;
	else
		dbit[victim_position]=0;
	
}

void op::run()
{
	int count = 0, tmp,next;
	ofstream rand_file("plot/random_result/opt_rand.txt");
	ofstream locality_file("plot/locality_result/opt_locality.txt");
	ofstream my_ref_file("plot/my_ref_result/opt_my_ref.txt");

	ofstream rand_int_file("plot/random_int_result/opt_int_rand.txt");
	ofstream locality_int_file("plot/locality_int_result/opt_int_locality.txt");
	ofstream my_ref_int_file("plot/my_ref_int_result/opt_int_my_ref.txt");

	ofstream rand_dis_file("plot/random_dis_result/opt_dis_rand.txt");
	ofstream locality_dis_file("plot/locality_dis_result/opt_dis_locality.txt");
	ofstream my_ref_dis_file("plot/my_ref_dis_result/opt_dis_my_ref.txt");
	//run each type of string
	for (int k = 0; k < 3; k++)
	{
		//input random,locality,my_ref string
		switch (k) {
		case 0:
			random_string1();
			cout << "Random string:" << endl;
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
		interrupt=vector<int>(10,0);
		diskIO=vector<int>(10,0);
		//run 10,20,30........,100 frames
		for (int i = 0; i < 10; i++) {

			num_frame = 10 * (i + 1);

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
			
			
			frame.resize(0);
			next_time.resize(0);
			dbit.resize(0);
			//input page
			for (int j = 0; j < times; j++) {
				//check whether page already in frame
				if ((tmp=already_in_frame(reference_string[j]))==-1) {

					//check whether frames are filled
					if (frame.size() == num_frame)
						change_victim_page(reference_string[j], j,i);
					else {
						frame.push_back(reference_string[j]);
						next=update_next_time(reference_string[j],j);
						next_time.push_back(next);
						double r=(double)rand()/RAND_MAX;
						if(r<update_pro)
							dbit.push_back(1);
						else
							dbit.push_back(0);
					}
					//increase page fault
					page_fault[i]++;
					
				}			
				else{
					next = update_next_time(reference_string[j], j);
					next_time[tmp] = next;
					double r=(double)rand()/RAND_MAX;
					if(r<update_pro)
						dbit[tmp]=1;
				
				}
				
				
			}
			interrupt[i]=diskIO[i]+page_fault[i];
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