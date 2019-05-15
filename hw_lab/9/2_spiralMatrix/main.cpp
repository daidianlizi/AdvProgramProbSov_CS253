#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
using namespace std;

void MyPrint(vector<vector<int>> res){
    for (int i = 0; i < res.size(); i++){
        for (int j = 0; j < res[0].size(); j++){
            cout << res[i][j]<<"  ";
        }
        cout<<endl;
    }
}
void SpiralMatrix(int row, int col){
    vector<vector<int>> res( row, vector<int>(col));
    int cnt = 1;
    int colbound = 0, rowbound = 0;
    while ( cnt <= row * col){
        int cp = colbound, rp = rowbound; //0. start point 
        //cout<<"round start at - cnt, colbound, rowbound: "<<cnt<<", "<<colbound<<", "<<rowbound<<endl;
        //cout<<"round start at - cp, rp: "<<cp<<", "<<rp<<endl;
        
        while ( cp < col - colbound ) //1. from left to right 
            res[rp][cp++] = cnt++;
        //cout<<"step 1: cnt = "<<cnt<<endl;

        rp = colbound + 1;
        cp = col - colbound - 1;
        while ( rp < row - rowbound)  //2. from top to bottom
            res[rp++][cp] = cnt++;
        //cout<<"step 2: cnt = "<<cnt<<endl;

        cp = col - colbound - 2;
        rp = row - rowbound - 1;
        while ( cp > (colbound - (row > col? 1: 0)))       //3. from right to left
            res[rp][cp--] = cnt++;
        //cout<<"step 3: cnt = "<<cnt<<endl;

        rp = row - rowbound - 1 - (row > col? 1: 0);
        cp = colbound;
        //cout<<"step 4 start - cp, rp, rowbound: "<<cp<<", "<<rp<<", "<<rowbound<<endl;
        while (rp > rowbound)        //4. from bottom to up
            res[rp--][cp] = cnt++;
        //cout<<"step 4: cnt = "<<cnt<<endl;

        colbound++;
        rowbound++;
        //cout<<"round finish at - cnt, colbound, rowbound: "<<cnt<<", "<<colbound<<", "<<rowbound<<endl<<endl;
    }
    cout <<"Formed Matrix: "<<endl;
    MyPrint(res);
}
int main() {
    int casenumber = 6;
    int row, col;
    switch (casenumber){
        case 1 : 
            row = 3;
            col = 4;
            break;
        case 2 : 
            row = 4;
            col = 3;
            break;
        case 3 : 
            row = 4;
            col = 6;
            break;
        case 4 : 
            row = 6;
            col = 4;
            break;
        case 5 : 
            row = 7;
            col = 4;
            break;
        case 6 : 
            row = 7;
            col = 7;
            break;
    }
    cout << "input row, col: "<<row<<", "<<col<<endl;
    SpiralMatrix(row, col);
    return 0;
}
