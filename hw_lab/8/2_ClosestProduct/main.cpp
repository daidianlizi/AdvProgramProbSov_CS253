#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <climits>
using namespace std;
void PrintVector(vector<int> arr, int len){
    for (int i = 0; i < len; i++){
        cout<<arr[i]<<"  ";
    }
    cout<<endl;
}
void MyPrint(vector<int> arr, int target, int len, int res_l, int res_r){
    //PrintVector(arr, len);
    cout << " The target is " << target<<endl; 
    cout << " The closest pair is " << arr[res_l] << " and " << arr[res_r]<<endl;
}
void CloestProductPair(vector<int> arr, int target, int len){
    int res_l, res_r;
    int l = 0, r = len -1, diff = INT_MAX;
    while (l < r){
        int tmpdiff = arr[l]*arr[r] - target;
        int absdiff = abs(tmpdiff);
        if ( absdiff < diff){
            res_l = l;
            res_r = r;
            diff = absdiff;
        }
        if ( tmpdiff > 0)
            r--;
        else 
            l++;
    }
    MyPrint(arr, target, len, res_l, res_r);
}
void MyQuickSort(vector<int>& arr, int low, int high){
    if (low >= high) return; //
    int pivot = arr[high]; //pivot
    int i = low -1; //index of the less/equal position
    for (int j = low; j < high; j++){ //j = low!!!
        if (arr[j] <= pivot){
            i++;
            swap(arr[i], arr[j]);//Finally place pivot at correct position by swapping arr[i+1] and arr[high] (or pivot) 
        }
        //cout<<arr.size()<<endl;
        //PrintVector(arr, arr.size());
    }
    swap(arr[++i], arr[high]);
    //PrintVector(arr, arr.size());
    //cout<<"one time recursive: i = "<<i<<endl;  
    MyQuickSort(arr, low, i - 1); 
    MyQuickSort(arr, i + 1, high);
}
int main() {
    //int a[] = {2,3,5,9};
    //int a[] = {9,5,3,2};
    //int a[] = {4,6,8,10,20,30};
    int a[] = {4,20,8,10,6,30};
    //int target = 8;
    //int target = 47;
    int target = 268;
    
    int len = sizeof(a) / sizeof(a[0]);
    //cout<<len<<endl;
    vector<int> arr(a,a+len);
    cout<<"input string: "<<endl;
    PrintVector(arr, len);
    //cout<<arr.size()<<endl;
    MyQuickSort(arr, 0, len-1);
    cout<<"finish sort, string is: "<<endl;
    PrintVector(arr, len);
    CloestProductPair(arr, target, len);
    return 0;
}
