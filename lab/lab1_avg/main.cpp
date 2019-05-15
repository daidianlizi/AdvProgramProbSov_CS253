#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv){
	//open file
	if (argc < 2){
		cout<<"You should input the file name.\n\n";
		return -0;
	}
	ifstream infile(argv[1]);
	if ( !infile.is_open() ){
		cout<<"Cannot open the file.\n\n";
		return -0;
	}

	//read file
	double int_temp;
	double sum = 0, count = 0, average = 0;
	while ( infile >> int_temp) {
		sum = sum + int_temp;
		count += 1;
	}
	infile.close();

	//calculate
	if (count == 0 ){
		cout<<"Your input file is empty.\n\n";
		return -0;
	} else{
		average = sum/count;
		cout<<"The average of the "<< count <<" numbers in file '" << argv[1] << "' is "<< average << endl<<endl;
		return 0;
	}
}