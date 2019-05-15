#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
using namespace std;

void MyPrint(int* input, int len){
    for (int i = 0; i < len; i++)
        //cout << *input++ <<"  ";
        cout << input[i] <<"  ";
    cout<<endl;
}
void MySwap(int gp, int bp, char* input){
    char tmp;
    tmp = input[gp];
    input[gp] = input[bp];
    input[bp] = tmp;
}
int RotatedSearch(int* input, int len, int tar){
    //find the index of the smallest value/ rotation point by binary search
    int lo =0, hi = len - 1;
    while (lo < hi){
        int mid = (lo + hi) >> 1;
        if (input[mid] > input[hi])
            lo = mid +1;
        else 
            hi = mid;
    }
    // lo == hi is the index 

    int rot = lo;
    lo = 0; hi = len -1;
    //the usral binary search and accounting for rotation
    while (lo <= hi){
        int mid = (lo + hi) >> 1;
        int realmid = (mid + rot)%len;
        if (input[realmid] == tar) 
            return realmid;
        if ( input[realmid] < tar)
            lo = mid +1;
        else 
            hi = mid -1;
    }
    return -1;
}
int main() {
    //int input[] = {13, 18, 25, 2, 8, 10}; //8---4
    //int input[] = {13, 18, 25, 64, 1, 2, 8, 10}; // 8----6
    //int tar = 8;
    int input[] = {1};
    int tar = 1;
    int len = sizeof(input)/sizeof(input[0]);
    cout <<"Input array: "<<endl;
    MyPrint(input, len);
    cout<<"Target: "<< tar<<endl;
    int res = RotatedSearch(input, len, tar);
    cout <<"Return the index in the array: "<<res<<endl;
    return 0;
}
