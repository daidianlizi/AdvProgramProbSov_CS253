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
		cout<<"itoa retult: "<<res2asc<<'\n';
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
	cout<<"itoa retult: "<<res2asc<<'\n';
}
void MyTestIntegers(char* input_string){
	int atoi_int = atoi(input_string);
	char itoa_string[20];
	itoa(atoi_int, itoa_string);
	if (strcmp(itoa_string, input_string) != 0)
		fprintf(stderr,"Wrong cast cmp! Input:%s,output_int:%d,output_str:%s|\n",input_string, atoi_int, itoa_string);
}
int main(int argc, char** argv){
	char input_string[20];
	while ( scanf("%s",input_string) != EOF ){
		MyTestIntegers(input_string);
	}
	/* open file in my way,
	if (0){
		if (argc < 2){
			cout<<"You choose to input number manually: \n";
			char input_string[20];
			cin >> input_string;
			MyTestIntegers(input_string);
		} 
		else if (argc == 2){
			char input_string[20];
			FILE *fp = fopen(argv[1],"r");
			if ( fp != NULL ){
				int row = 0;
				while ( fscanf(fp,"%s",input_string) != EOF ){
					row++;
					MyTestIntegers(input_string);
				}
				fclose(fp);
			}
			else cout<<"Cannot open the file.\n";
		}
		else cout<<"Your input file name should not have space. \n";
	}
	*/
}

