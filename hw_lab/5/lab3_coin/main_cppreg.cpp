#include <iostream>
#include <cstdio>
#include <math.h>
#include <vector>
#include <math.h>
using namespace std;


float MyMax3(float a, float b, float c){
    float tmp;
    tmp = max(a,b);
    return max(tmp, c);
}
float MyMax4(float a, float b, float c, int d){
    float tmp;
    tmp = MyMax3(a,b,c);
    return max<float>(tmp, d);
}
void MyParse(string line, smatch numberResult, regex ip_reg){
    //10p 10n 10d 10q 255
    if (regex_match(line, numberResult, ip_reg))
        {
            cout << "Match: ";
            //打印子表达式结果
            for (size_t i = 1; i < matchResult.size(); ++i)
            {
                cout << matchResult[i] << " ";
            }
        }
        else
        {
            cout << "Not Match!";
        }
}
void PrintFormat(string S1, string S2, vector<vector<float>> H, int size1, int size2){
    cout <<'\t'<<'\t';
    for (int j = 0; j< size2; j++){
        cout<<S2[j]<<'\t';
    }
    cout<<'\n';
    for (int i = 0; i < size1; i++){
        if (i >= 1)
            cout<<S1[i-1]<<'\t';
        else
            cout<<'\t';
        for (int j = 0; j< size2; j++){
            cout<<H[i][j]<<'\t';
        }
        cout<<'\n';
    }
}

void OptimalLocalAlign(string S1, string S2){
    int size1 = S1.size() + 1;
    int size2 = S2.size() + 1;
    vector<vector<float>> H(size1, vector<float>(size2));
    //initialize
    float maxscore = 0;
    pair<int, int> maxlocation;
    for (int i = 0; i < size1; i++){
        H[i][0] = 0;
    }
    for (int j = 1; j < size2; j++){
        H[0][j] = 0;
    }
    for (int i = 1; i < size1; i++){
        for (int j = 1; j< size2; j++){
            H[i][j] = MyMax4( H[i-1][j-1] + SubstitutionMatrix(S1[i-1],S2[j-1]),
                            H[i][j-1] - Penalty(),
                            H[i-1][j] - Penalty(),
                            0);
            if (H[i][j] > maxscore){
                maxscore = H[i][j];
                maxlocation = make_pair(i,j);
            }
        }
    }
    cout<<"maxscore: "<<maxscore<<endl;
    int remainvalue = maxscore;
    PrintFormat(S1,S2,H,size1,size2);
    cout<<"the back path found:\n";
    BackTracePrint(H, maxlocation, S1, S2, remainvalue);
}
int main(){
    string line;
    regex ip_reg("(.*)\p(.*)\n(.*)\d(.*)\q (.*)");//10p 10n 10d 10q 255
    smatch NumberResult;
    vector<int> ValueList = {1,5,10,25};
    while ( getline(cin,line) != EOF){
        MyParse(line, numberResult, ip_reg);
        //Calculate(line);
        //PrintFormat();
    }
    return 0;
}
