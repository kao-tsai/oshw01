#include<iostream>
#include"FIFO.h"
#include"op.h"
#include"esc.h"
#include"lru.h"
#include"lru2.h"
#include"sc.h"
#include"lfu.h"
#include"lrusc.h"
using namespace std;

void random_string() {
	srand(time(0));
	ofstream output("random_string.txt");
	int random_num;
	int times = 100000;
	for (int i = 0; i < times; i++)
	{
		random_num = rand() % 500 + 1;
		output << random_num<<" ";
	}
	output.close();
} 
/*
void locality_string2() {
	ofstream output("locality_string.txt");
	int times = 100000;
	int locality_num, start_num,count=0,tmp;


	while (count < times) {

		locality_num = rand()%26+25;
		start_num = rand() % 500;

		for(int i=0;i<locality_num;i++){
				tmp=start_num+i;
				if(tmp>500)
					output<<tmp%500<<" ";
				else
					output<<tmp<<" ";
		}
		
		count+=locality_num;
	}
	output.close();
}*/

void locality_string2() {
	ofstream output("locality_string.txt");
	int times = 100000;
	int locality_num, rate, start_num, num_func_calls,random_num,count=0;
	while (count < times) {

		rate = rand() % 11 + 10;
		locality_num = 500 / rate;
		start_num = rand() % 500;

		num_func_calls = rand() % 2 + 50;
		for (int i = 0; i < num_func_calls; i++) {
			random_num = rand() % locality_num+start_num;
			if(random_num>500)
				output<<random_num%500<<" ";
			else
				output << random_num << " ";
			count++;
		}
		
	}
	output.close();

}
/*
void bubble_sort_string(){
	ofstream output("bubble_sort_string.txt");
	int sort_size,count=0,times=100000,start_num;
	while(count<times){
		sort_size=rand()%30+10;
		start_num=rand()%500+1;
		for(int i=0;i<sort_size-1;i++){
				for(int j=i;j<sort_size-1;j++){
						if(start_num>500)
								output <<(start_num+j)%500<<" "<<(start_num+j+1)%500<<" ";
						else
								output <<start_num+j<<" "<<start_num+j+1<<" ";
						count+=2;
				}
		}
	}
	output.close();
}*/
// void selection_sort_string(){
// 	ofstream output("my_ref_string.txt");
// 	int sort_size,count=0,times=100000,start_num,tmp;
// 	while(count<times){
// 		sort_size=rand()%50+20;
// 		start_num=rand()%500+1;
// 		for(int i=0;i<sort_size-1;i++){
// 				for(int j=i;j<sort_size-1;j++){
// 						tmp=start_num+j;
						//   if(tmp>500)
						// 	      output <<tmp%500<<" ";
						//   else
						// 		  output <<tmp<<" ";
// 						count++;
// 				}
// 		}
// 	}
// 	output.close();
// }

void s_selection_sort_string(){
	ofstream output("my_ref_string.txt");
	int sort_size,count=0,times=100000,start_num,start_num2,tmp;
	while(count<times){
		sort_size=rand()%190+50;//50 20
		start_num=rand()%500+1;//500 1
		start_num2=start_num+sort_size-1;
		for(int i=0;i<sort_size-1;i++){
				for(int j=i;j<sort_size;j++){
					if(i%2==0){

						tmp=start_num+(i/2);
						tmp=tmp+(j-i);
						if(tmp>500)
								output <<tmp%500<<" ";
						else
								output <<tmp<<" ";

					}
					else{
						
						tmp=start_num2-(i/2);
						tmp=tmp-(j-i);
						if(tmp>500)
								output <<tmp%500<<" ";
						else
								output <<tmp<<" ";

					}
					
					count++;
				}
		}
	}
	output.close();

}
int main() {
	random_string();
	locality_string2();
	s_selection_sort_string();
	FIFO fifo;
	op optimal;
	lru2 lrur2;
	sc scr;
	lfu lfur;
	lrusc lruscr;
	esc es;
	cout << "FIFO Algo:" << endl<<endl;
	fifo.run();
	cout << endl<<"Optimal Algo:" << endl<<endl;
	optimal.run();
	cout << endl << "ESC Algo:" << endl << endl;
	es.run();
	// cout << endl<< "lru2 Algo:" << endl<< endl;
	//lrur2.run();
	// cout << endl<< "sc Algo:" << endl<< endl;
	// scr.run();
	// cout << endl<< "LFU Algo:" << endl<< endl;
	// lfur.run();
	cout << endl<< "lrusc Algo:" << endl<< endl;
	lruscr.run();
	return 0;
}