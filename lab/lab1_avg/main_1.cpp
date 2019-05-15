#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main(){
	ifstream infile("./file.dat");
	string temp;
	int int_temp;
	int sum = 0, count = 0, average = 0;
	if ( !infile.is_open() ){
		cout<<"cannot open the file.\n";
		return -1;
	}
	while ( getline(infile, temp) ){
	stringstream(temp) >> int_temp;
		cout<<int_temp<<"\n";
		sum = sum + int_temp;
		count += 1;
	}
	infile.close();
	average = sum/count;
	cout<<"The average of the "<< count <<" numbers in file “numbers.dat” is "<< average << endl;
	return average;
}