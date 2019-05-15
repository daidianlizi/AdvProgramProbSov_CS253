#include <iostream>
#include <fstream>
#include <stdio.h>
#include "string.h"
using namespace std;

int atoi(char* input_string){
	int high = strlen(input_string)-1, low = 0;
	int flag = 1;
	if (input_string[0] == '-') {
		flag = -1;
		low = 1;
	}
	int res2int = 0;
	for (int i = low; i <= high; i++){
		res2int = res2int*10 + input_string[i] - '0';
	}
	return res2int*flag;
}
void swap(char* res2asc, int low, int high){	
	while(low<=high){
		char tmp = res2asc[low];
		res2asc[low] = res2asc[high];
		res2asc[high] = tmp;
		low++; high--;
	}
}
void itoa(int input_int, char* res2asc){
	if (input_int==0){
		strcpy(res2asc,"0");
		printf("%s\n",res2asc);
		return;
	}
	int low = 0;
	if (input_int < 0 ){
		low = 1;
		res2asc[0] = '-';
		input_int = -input_int;
	}
	int high = low;
	while (input_int!=0) { 
		res2asc[high] = input_int%10 + '0';
		input_int/=10;
		high++;
	}
	high--;
	res2asc[high+1] = '\0';
	swap(res2asc,low,high);
	printf("%s\n",res2asc);
}
void MyTestIntegers(char* input_string){
	int atoi_int = atoi(input_string);
	char itoa_string[20];
	itoa(atoi_int, itoa_string);
	if (strcmp(itoa_string, input_string) != 0)
		fprintf(stderr,"Wrong cast!input:%s,output_int:%d,output_str:%s|\n",input_string,atoi_int,itoa_string);
}
int main(int argc, char** argv){
	//open file
	if (argc < 2){
		cout<<"You choose to input number manually: \n";
		char input_string[20];
		cin >> input_string;
		MyTestIntegers(input_string);
	} 
	else if (argc == 2){
		char input_string[20];
		ifstream infile(argv[1]);
		if ( infile.is_open() ){
			while ( infile.getline(input_string,20) ){
				cout<<input_string[0]<<'\n';
				MyTestIntegers(input_string);
			}
			infile.close();
		}
		else cout<<"Cannot open the file.\n";
	}
	else cout<<"Your input file name should not have space. \n";
}

