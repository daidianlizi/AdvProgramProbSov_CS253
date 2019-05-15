#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
using namespace std;

int a[5] = {2,3,5,7,11};
vector<int> primeset(a, a + 5);
bool isprime(int value ){
    for (int i = 2; i <= sqrt(value); i++){
        if (value % i == 0)
            return false;
    }
    return true;
}
void constructPrimeSet(int num){
    int size = primeset.size();
    int i = primeset[size - 1] + 1;
    do {
        if ( isprime(i) )
            primeset.push_back(i);
        i++;
    }while(i <= num);
}
void checkPrimeSet(int num){
    int size = primeset.size();
    if (primeset[size - 1] < num)
        constructPrimeSet(num);
}
void printPrime(int num){
    if (num <= -1) {
        cout << num <<": no prime.\n";
    }
    //cout << num <<": has prime of: "<<endl;
    cout << num <<": has prime of: ";
    for (int i = 0; primeset[i] <= sqrt(num); i++){
        //cout<<"i, prime: "<< i << ","<<primeset[i]<<endl;
        while (num % primeset[i] == 0){
            if (num/primeset[i] == 1)
                printf("%d\n",primeset[i]);
            else 
                printf("%d * ",primeset[i]);
            //cout<<"num, prime: "<< num << ","<<primeset[i]<<endl;
            num /= primeset[i];
            //cout<<"new num "<< num << endl;
        }
    }
    if (num > 2)
        printf("%d\n", num);
}
int main(){
    ifstream in("input.txt");
    int num;
    string mynum;
    //cout <<"initial test: " << primeset[6]<<endl;
    while (getline(in, mynum)){
        stringstream(mynum) >> num;
        //cout<<num<<endl;
        checkPrimeSet(num);
        //cout << "constructPrimeSet for " << num << " until " << primeset.back() << endl;
        printPrime(num);
    }
    in.close();
    return 0;
}