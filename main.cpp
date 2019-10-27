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

//產生random reference string
void random_string() {
	srand(time(0));
	//將字串寫在"random_string.txt"裡
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
//產生locality reference string
void locality_string2() {
	//將字串寫在"locality_string.txt"裡
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
//產生my reference string
void s_selection_sort_string(){
	//將字串寫在"my_ref_string.txt"裡
	ofstream output("my_ref_string.txt");
	int sort_size,count=0,times=100000,start_num,start_num2,tmp;
	//EXAMPLE:7 6 5 4 1 共5個page做selection sort
	// 搜尋順序:
	// 76541
	// 1456
	// 654
	// 45
	// 5
	while(count<times){
		sort_size=rand()%150+50;//200 250
		start_num=rand()%500+1;
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
	lrusc lruscr;
	esc es;
	cout << "FIFO Algo:" << endl<<endl;
	fifo.run();
	cout << endl<<"Optimal Algo:" << endl<<endl;
	optimal.run();
	cout << endl << "ESC Algo:" << endl << endl;
	es.run();
	cout << endl<< "lrusc Algo:" << endl<< endl;
	lruscr.run();
	return 0;
}