#include <iostream>
#include <cstdio>
#include <math.h>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
const int MY_LIMIT = -2e9;

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
bool MyParse(FILE *fp, int* &pcn, int& target_value){
    //10p 10n 10d 10q 255
    static int countline = 0;
    countline++;
    cout<<"processing input line: "<<countline<<endl;
    if (fscanf(fp, "%dp %dn %dd %dq %d\n", pcn, pcn+1, pcn+2, pcn+3, &target_value)!= EOF){
        return true;
    }
    else{
        cout<<"finished or wrong\n";
        return false;
    }
}

void PrintFormat(int* cv, int tv, vector<vector<float>> H, int size1, int size2){
    cout <<'\t';
    for (int j = 0; j< size2; j++){
        cout<<j<<'\t';
    }
    cout<<'\n';
    for (int i = 0; i < size1; i++){
        if (i >= 1)
            cout<<cv[i-1]<<'\t';
        else
            cout<<'\t';
        for (int j = 0; j< size2; j++){
            cout<<H[i][j]<<'\t';
        }
        cout<<'\n'<<'\n';
    }
}
void BackTracePrint(int* cn, int remainvalue, int* cv, vector<vector<float>> H, int size1, int size2, int maxcoins){
    vector<int> coin_use(maxcoins, 0);
    for (int i = size1 - 1; i > 0; i--){
        int maxK = min(cn[i-1],remainvalue/cv[i-1]);
        cout<<"coin value: "<<cv[i-1]<<", remainvalue: "<<remainvalue<<", maxK: "<<maxK<<endl;
        for (int k = 0; k <= maxK; k++){
            int prevcn = H[i-1][remainvalue - k * cv[i-1]];
            cout<<"test one: k = "<<k<<", prevcn: "<<prevcn<<endl;
            if (prevcn + k == maxcoins){
                maxcoins -= k;
                cout<<"renew one: k = "<<k<<", maxcoins: "<<maxcoins<<endl;
                remainvalue -= k * cv[i-1];
                coin_use[i-1] = k;
                break;
            }
        }
    }
    char coin_memo[4] = {'p','n','d','q'};
    for (int i = 0; i < size1 -1; i++){
        cout<<coin_use[i]<<coin_memo[i]<<" ";
    }
    cout<<"\n";
}
void MaxCalculate(int* cn, int tv, int* cv){
    int size1 = 4 + 1;
    int size2 = tv + 1;
    int MAXCOIN = cn[0]+cn[1]+cn[2]+cn[3]+1;
    //cout<<size1<<endl;
    //cout<<size2<<endl;
    cout<<MAXCOIN<<endl;
    vector<vector<float>> H(size1, vector<float>(size2));//H[i][j],first i kinds of coins for j target value.
    //initialize
    pair<int, int> maxlocation;
    for (int i = 0; i < size1; i++)
        H[i][0] = 0;
    for (int j = 1; j < size2; j++)
        H[0][j] = MY_LIMIT;
    
    //transfer
    //cn,cv is 0 base, H can be thought as 1 base
    cout<<"trans"<<endl;
    for (int i = 1; i < size1; i++){
        for (int j = 1; j< size2; j++){
            //cout<<cn[i-1]<<endl;
            H[i][j] = H[i-1][j];
            int maxK = min(cn[i-1],j/cv[i-1]);
            cout<<"i, j, maxK: "<<i<<","<<j<<","<<maxK<<endl;
            for (int k = 1; k <= maxK; k++){
                    float prevcn = H[i-1][j - k * cv[i-1]];
                    cout<<"maxK: k, prevcn: "<<maxK<<": "<<k<<","<<prevcn<<endl;
                    //T O(nm^2)
                    if( prevcn > MY_LIMIT ){ //> for max, < for min
                            H[i][j] = max( H[i][j], prevcn + k);
                            cout<<"renwe H[i][j]: "<<H[i][j]<<endl;
                        }
                    
            }
        }
    }
    //result
    cout<<"res"<<endl;
    int maxcoins = H[size1 -1 ][size2 -1];
    cout << "no filter maxcoins: " << maxcoins<<endl;
    if(0 < maxcoins < MAXCOIN){
        cout << "maxcoins: " << maxcoins<<endl;
    }
    else
        cout<<"not found.\n";

    PrintFormat(cv, tv, H, size1, size2);
    //cout<<"the back path found:\n";
    int remainvalue = tv;
    BackTracePrint(cn, remainvalue, cv, H, size1, size2, maxcoins);
    //PrintResult(S1,S2,H,size1,size2);
}
int main(int argc, char** argv){
    if (argc < 2){
        cout<<"please input filename"<<endl;
        return -1;
    }
    FILE *fp = fopen(argv[1],"r"); 
    int coin_numbers[4];
    int *pcn = coin_numbers;
    int target_value;
    int coin_value[4] = {1,5,10,25};
    while ( MyParse(fp, pcn, target_value) ){
        for (int i = 0; i < 4; ++i){
            cout << *(pcn+i) << " ";
            //cout << coin_numbers[i]<< " ";
        }
        cout << target_value << endl;
        MaxCalculate(coin_numbers, target_value, coin_value);
    }
    fclose(fp);
    return 0;
}