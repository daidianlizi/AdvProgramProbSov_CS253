#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

void MyPrint(vector<int> vc){
    for (int i = 0; i < vc.size(); i++)
        cout <<vc[i];
    cout<<endl;
}
void nextpermutation(vector<int> input){
    int n = input.size();
    int left = -1;
    for (int i = n-1; i > 0; i--){
        if (input[i-1] < input[i]){
            left = i - 1;
            break;
        }
    }

    if (left == -1){
        reverse(input.begin(), input.end());
        cout <<"next permutation: ";
        MyPrint(input);
        return;
    }

    int right = 0;
    for (int i = n-1; i > 0; i--){
        if (input[i] > input[left]){
            right = i;
            break;
        }
    }
    swap(input[left], input[right]);
    reverse(input.begin()+left+1, input.end());
    cout <<"next permutation: ";
    MyPrint(input);
}
int main() {
    //int a[] = {1,2,3};
    //int a[] = {3,2,1};
    //int a[] = {1,1,5};
    int a[] = {5,6,3,2,2};
    int len = sizeof(a)/sizeof(a[0]);
    vector<int> input(a, a+len);
    cout <<"this permutation: ";
    MyPrint(input);
    nextpermutation(input);
    return 0;
}
