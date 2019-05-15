#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    int MyMax = 4000000;
    vector<int> nums(MyMax,0);
    int sum = 0;
    nums[0] = 1;
    nums[1] = 1;
    int i = 2;

    while ( true){
        nums[i] = nums[i-1] + nums[i-2];
        if (nums[i] > MyMax)
            break;
        cout<<nums[i]<<endl;
        if (nums[i]%2 == 0){
            sum += nums[i];
        }
        i++;
    }
    cout<<sum;
    return 0;
}
