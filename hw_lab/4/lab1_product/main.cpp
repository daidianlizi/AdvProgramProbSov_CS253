#include <iostream>
using namespace std;

int main(){
    int a[1000];
    long product_prefix[1000];
    long* result = product_prefix;
    int n; cout<<"input the number of integers\n"; cin>>n;
    if (n > 1000 || n <= 3){
        cout<<"Number of integers should be lt 1000 and gt 3\n";
        return -1;
    }
    cout<<"input integers\n";
    for (int i = 0; i < n ; i++){
        cin >> a[i];
        product_prefix[i] = i == 0? 1 : product_prefix[i-1]*a[i-1];
    }
    long product_suffix, product;
    for (int i = n - 1; i >= 0; i--){
        product_suffix = i == (n-1)? 1 : product_suffix * a[i+1];
        product_prefix[i] = product_prefix[i] * product_suffix;
    }
    for (int i = 0; i < n; i++){
        cout<< *result++ << endl;
    }
    return 0;
}