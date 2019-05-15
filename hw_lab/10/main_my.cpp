#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    int MyMax = 4000000;
    int num1 = 1;
    int num2 = 2;
    int sum = 0;
    int tmp;
    while (num1 < MyMax){
        if (num1%2 == 0){
            sum += num1;
        }
        tmp = num2 + num1;
        num1 = num2;
        num2 = tmp;
    }
    cout<<sum;
    return 0;
}
