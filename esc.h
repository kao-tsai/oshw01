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
	double update_pro;
	vector<int> page_fault;
	vector<int> interrupt;
	vector<int>diskIO;
	vector<int>frame;
	vector<int>rbit;
	vector<int>dbit;
};

//初始各個參數
esc::esc() {
	srand(time(NULL));
	num_frame = 10;
	times = 100000;
	page_fault = vector<int>(10, 0);
	interrupt = vector<int>(10, 0);
	diskIO = vector<int>(10, 0);
	update_pro=0.3;
}
//讀入random string資料
void esc::random_string1() {
	reference_string.resize(times);

	ifstream input("random_string.txt");
	for (int i = 0; i < times; i++)
		input >> reference_string[i];

	input.close();
}
//讀入locality string資料
void esc::locality_string2() {
	reference_string.resize(times);
	ifstream input("locality_string.txt");

	for (int i = 0; i < times; i++)
		input >> reference_string[i];

	input.close();
}
//讀入我的reference string資料
void esc::my_ref_string3() {
	reference_string.resize(times);
	ifstream input("my_ref_string.txt");

	for (int i = 0; i < times; i++)
		input >> reference_string[i];
	input.close();
}
//檢查page是否在memory裡 有就回傳位置 沒有傳回-1
int esc::already_in_frame(int page) {
	for (int i = 0; i < frame.size(); i++)
		if (page == frame[i])
			return i;

	return -1;
}
//enhanced second chance演算法
void esc::change_victim_page(int page,int current_frame_num) {
	
	bool flag=false;

	for(int i=0;i<2;i++){
		for(int j=0;j<frame.size();j++)
			//找出rbit和dbit均為0的分頁為替換分頁
			if(rbit[j]==0&&dbit[j]==0){
				rbit.erase(rbit.begin()+j);
				dbit.erase(dbit.begin()+j);
				frame.erase(frame.begin()+j);
				frame.push_back(page);	
				rbit.push_back(1);
				//決定新分頁的dirty bit值
				double r=(double)rand()/RAND_MAX;
				if(r<update_pro)
					dbit.push_back(1);
				else
					dbit.push_back(0);
				flag = ~flag;
				break;
			}

		//已找到犧牲分頁結束演算法
		if(flag)
			break;

		//找出rbit為0和dbit為1的分頁為替換分頁，若不是則把rbit清掉
		for (int j = 0; j < frame.size(); j++)
			if(rbit[j]==0&&dbit[j]==1){
				rbit.erase(rbit.begin()+j);
				dbit.erase(dbit.begin()+j);
				frame.erase(frame.begin()+j);
				frame.push_back(page);
				rbit.push_back(1);
				//決定新分頁的dirty bit值
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

		//已找到犧牲分頁結束演算法
		if(flag)
		{
			//dirty bit為1寫回disk
			diskIO[current_frame_num]++;
			break;
		}
	}
	
}
//執行enhanced second chance演算法
void esc::run()
{
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

	//執行3個不同的reference string(random,locality,my_reference_string)
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
			cout<<"My Reference string:"<<endl;
			my_ref_string3();
	
		}

		page_fault = vector<int>(10, 0);
		interrupt = vector<int>(10, 0);
		diskIO = vector<int>(10, 0);
		//執行10個不同frame數(10,20,30,40............100)
		for (int i = 0; i < 10; i++) {
			num_frame = 10 * (i + 1);
			frame.clear();
			rbit.clear();
			dbit.clear();
			//執行100000筆reference string
			for (int j = 0; j < times; j++) {
				//page沒有在memory裡傳回-1
				if ((tmp = already_in_frame(reference_string[j])) == -1) {

					//frame若滿了移除犧牲分頁
					if (frame.size() == num_frame)
						change_victim_page(reference_string[j],i);

					//frame若未滿將新分頁加入memory
					else
					{
						frame.push_back(reference_string[j]);
						rbit.push_back(1);

						//決定新分頁的dirty bit值
						double r = (double)rand() / RAND_MAX;
						if (r < update_pro)
							dbit.push_back(1);
						else
							dbit.push_back(0);
					}
					//分頁錯誤加1
					page_fault[i]++;
							
				}
				//page在memory裡回傳page位置
				else{
					//分頁hit將rbit設成1
					rbit[tmp] = 1;
					//決定分頁的dirty bit值
					double r = (double)rand() / RAND_MAX;
					if (r < update_pro)
						dbit[tmp]=1;
					
				}
			}
			//寫回硬碟和分頁錯誤均會發生中斷將兩個相加即是中斷數
			interrupt[i]=page_fault[i]+diskIO[i];
			cout << "Frame size:" << num_frame << ": " << page_fault[i] << endl;

			//將所有三種字串和中斷，分頁錯誤，硬碟寫回結果寫檔輸出
			switch (k) {
			case 0:
				rand_file<<num_frame<<" "<<page_fault[i]<<endl;
				rand_int_file<<num_frame<<" "<<interrupt[i]<<endl;
				rand_dis_file<<num_frame<<" "<<diskIO[i]<<endl;
				break;

			case 1:
				locality_file<<num_frame<<" "<<page_fault[i]<<endl;
				locality_int_file<<num_frame<<" "<<interrupt[i]<<endl;
				locality_dis_file<<num_frame<<" "<<diskIO[i]<<endl;
				break;

			case 2:
				my_ref_file<<num_frame<<" "<<page_fault[i]<<endl;
				my_ref_int_file<<num_frame<<" "<<interrupt[i]<<endl;
				my_ref_dis_file<<num_frame<<" "<<diskIO[i]<<endl;

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