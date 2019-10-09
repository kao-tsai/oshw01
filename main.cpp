#include<iostream>
#include"FIFO.h"
#include"op.h"
#include"esc.h"
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
void locality_string2() {
	ofstream output("locality_string.txt");
	int times = 100000;
	int locality_num, rate, start_num, num_func_calls,random_num,count=0;
	while (count < times) {

		rate = rand() % 11 + 10;
		locality_num = 500 / rate;
		start_num = rand() % 500;

		num_func_calls = rand() % 1000 + 5000;
		for (int i = 0; i < num_func_calls; i++) {
			random_num = (rand() % locality_num+start_num)%500+1;
			output << random_num << " ";
			count++;
		}
		
	}
	output.close();

}
int main() {
	
	random_string();
	locality_string2();
	FIFO fifo;
	op optimal;
	esc es;
	cout << "FIFO Algo:" << endl<<endl;
	fifo.run();
	cout << endl<<"Optimal Algo:" << endl<<endl;
	optimal.run();
	cout << endl << "ESC Algo:" << endl << endl;
	es.run();

	return 0;
}