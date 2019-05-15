#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <cmath>
#include <utility>
using namespace std;

int main() {
    string infile = "aggregation.txt";
    int N=788, k=7;
    fstream in;
    in.open(infile);

    fstream outfile;
    //outfile.open("clustering.txt", ios::out);
    outfile.open("aggregation_format.txt", ios::out);
    outfile<<N<<endl;
    outfile<<k<<endl;

    int count = 0;
    while( !in.eof() ){
        int i;
        float x, y;
        in >> x >> y >> i;
        cout<<x<<" "<<y<<" "<<i<<" "<<endl;
        outfile<<count+1<<" "<< x <<" " << y <<endl;
        count++;
    }
    in.close();   
    cout<<"Read data successfully!"<<endl;

    return 0;
}
