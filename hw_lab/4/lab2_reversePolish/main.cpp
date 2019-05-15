#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <cstdio>
#include <math.h>

using namespace std;
bool constructData(int &i, string &line, int size,string &tmp, vector<string> &result){
    if (isdigit(line[i])){
        while( i < size && isdigit(line[i])){
            tmp = tmp + line[i];
            i++;
        }
        result.push_back(tmp);
        i--;
        return true;
    }
    return false;
}
vector<string> ProcessRPN(string &line){
    vector<string> result;
    int size = line.size();
    for (int i = 0; i < size; i++){
        //cout<<"i_tmp: "<<i<<","<<line[i]<<endl;
        //skip space
        if (line[i] == ' ' || line[i] == '\t') {
            continue;
        }
        //extract operations
        switch (line[i]) {
            case '-': 
                if (!isdigit(line[i+1])){
                    result.push_back(string(1,line[i]));
                    continue;
                }
                else {
                    string tmp;
                    tmp = tmp + line[i];
                    i++;
                    constructData(i,line,size,tmp,result);
                    //cout<<"tmp: "<<i<<","<<tmp<<endl;
                    continue; 
                }
            case '+': 
            case '*': 
            case '/': 
            case 'p':
            case 's':
            case 'd':
                result.push_back(string(1,line[i]));
                continue;
        }
        //extract numbers
        string tmp;
        if (constructData(i,line,size,tmp,result)){
            continue;
        }
        else 
            printf("wrong input char %d: %d,%c\n", i, line[i], line[i]);
    }
    //cout<<"process finished\n";
    return result;
}
float ReversPolishNotationCalculate(string &line){
    vector<string> processRPN = ProcessRPN(line);
    stack<float> nums;
    float res;
    //cout<<"cal begin\n";
    for (int i = 0; i < processRPN.size(); i++){
        //cout <<i<<","<<processRPN[i]<<endl;
        if ( isdigit(processRPN[i][0]) || processRPN[i].size() > 1 )
            nums.push( atoi(processRPN[i].c_str()) );
        else{
            switch (processRPN[i][0]){
                case 'p': 
                    printf("%.0f\n", nums.top());
                    continue;
                case 'd':
                    nums.push(nums.top());  
                    continue;
            }
            float num2 = nums.top();
            nums.pop();
            float num1 = nums.top();
            nums.pop();
            switch (processRPN[i][0]){
                case '+': 
                    nums.push(num1 + num2);
                    continue;
                case '-': 
                    nums.push(num1 - num2);
                    continue;
                case '*':
                    nums.push(num1 * num2); 
                    continue;
                case '/': 
                    nums.push(floor(num1 / num2));
                    continue;
                case 's':
                    nums.push(num2);
                    nums.push(num1);
                    continue;
            }
        }
    }
    res = nums.top();
    //cout<<"res: " << res<<endl;
    return nums.top();
}
int main(int argc, char* argv[]){
    ifstream infile(argv[1]);
    string line;
    if (infile.is_open()){
       while ( getline(infile,line) ){
            //cout<<"processing\n";
            ReversPolishNotationCalculate(line);
            //cout<<"next\n";
        } 
        infile.close();
    }
    else cout << "unable to open file";  
    cout<<"success!\n";
    return 0;
}