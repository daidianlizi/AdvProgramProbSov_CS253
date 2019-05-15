#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
using namespace std;

void Longestk(string str, int k){
    int len = str.size();
    string res;
    int reslen = 0, res_l = 0;
    unordered_map<char, int> m;
    int left = 0;
    for (int i = 0; i < len; i++){
        ++m[str[i]];
        while ( m.size() > k ){
            if ( --m[str[left]] == 0)
                m.erase(str[left]);
            ++left;
        }
        if (reslen < i - left + 1){
            reslen = i - left +1;
            res_l = left;
        }
    }
    res = str.substr(res_l, reslen); 
    cout <<"input str: "<<str<<endl;
    cout <<"k: "<<k<<endl;
    cout <<"res: "<<res<<endl;
}
int main() {
    int casenumber = 1;
    string str;
    int k;
    switch (casenumber){
        case 1 : 
            str = "abcbbbbcccbdddadacb";
            k = 2;
            break;
        case 2 : 
            str = "abcbbbbcccbdddadacb";
            k = 3;
            break;
        case 3 : 
            str = "helloooowo";
            k = 2;
            break;
    }
    Longestk(str, k);
    return 0;
}
