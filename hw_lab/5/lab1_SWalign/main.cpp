#include <iostream>
#include <cstdio>
#include <math.h>
#include <vector>
#include <math.h>
using namespace std;

#define subvalue 3
#define pnlvalue 2
float SubstitutionMatrix(char a, char b ){
    float sub = (a==b)? subvalue: -subvalue;
    return sub;
}
float Penalty(){
    float pnl = pnlvalue;
    return pnl;
}
int remainvalue;
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
void prev(int& i, int& j, vector<vector<float>> H, string& out1, string& out2, int &remainvalue){
    //i,j is for in H        
    float a = H[i-1][j-1] + SubstitutionMatrix(out1[i-1],out2[j-1]);
    float b = H[i-1][j] - Penalty();
    float c = H[i][j-1] - Penalty();
    float maxprev = MyMax3(a,b,c);
    //cout<<a<<b<<c<<endl;
    //cout<<out1[i-1]<<out2[j-1]<<SubstitutionMatrix(out1[i-1],out2[j-1]);
    cout<<remainvalue<<endl;
    if (maxprev == a){
        remainvalue -= SubstitutionMatrix(out1[i-1],out2[j-1]);
        if (remainvalue == 0)//the only possible ending point is from this slash case
            return;
        i = i-1;
        j = j-1;   
    }
    else if (maxprev == b){
        remainvalue += Penalty();
        out2.insert(j,"-"); //j-1+1
        i = i-1;
        j = j;
    }
    else {
        remainvalue += Penalty();
        out1.insert(i,"-");//i-1+1
        i = i;
        j = j-1; 
    }
}
void BackTracePrint(vector<vector<float>> H, pair<int, int> maxlocation, string S1, string S2, int &remainvalue){
    int i = maxlocation.first;
    int j = maxlocation.second;
    //here transfer to the loctaion in S1, S2, thus -1 than in the matrix.
    int si = i - 1;
    int sj = j - 1;
    string out1 = S1.substr(0,si+1);
    string out2 = S2.substr(0,sj+1);
    while (remainvalue != 0){
            prev(i,j,H,out1,out2,remainvalue);
    }
    out1 = out1.substr( i - 1, out1.size() - i + 1 );
    out2 = out2.substr( j - 1, out2.size() - j + 1);
    cout<<"S1 = "<<out1<<endl;
    cout<<"S2 = "<<out2<<endl;
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
    //string S1 = "ACACACTA";
    //string S2 = "AGCACACA";
    //string S1 = "GGTTGACTA";
    //string S2 = "TGTTACGG";
    string S1 = "AGGGCT"; 
    string S2 = "AGGCA";
    OptimalLocalAlign(S1, S2);
    return 0;
}
