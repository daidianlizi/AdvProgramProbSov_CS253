#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int main(){
    ifstream in("rand_numbers.txt");
    ofstream odd("odd.txt");
    ofstream even("even.txt");
    vector<int> nums;
    copy(istream_iterator<int>(in),
        istream_iterator<int>(),
        back_inserter(nums) );
    sort( begin(nums), end(nums) ); // sort all the nums
    //cout<<*begin(nums)<<endl;
    //copy( begin(nums), end(nums), ostream_iterator<int>(cout, "\n") );
    auto lambdaWrite = [&even, &odd](const int& cur){
        (cur % 2) == 0? (even << cur << "\t") : (odd << cur << "\t");
    };
    for_each( begin(nums), end(nums),lambdaWrite);
    cout<<"successed in process and save!\n";
    in.close();
    odd.close();
    even.close();
    return 0;
}