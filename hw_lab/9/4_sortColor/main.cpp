#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
using namespace std;

void MyPrint(char* input, int len){
    for (int i = 0; i < len; i++)
        //cout << *input++ <<"  ";
        cout << input[i] <<"  ";
    cout<<endl;
}
void MySwap(int gp, int bp, char* input){
    char tmp;
    tmp = input[gp];
    input[gp] = input[bp];
    input[bp] = tmp;
}
void SegregateColor(char* input, int len){
    int rp = 0, gp = 0, bp = len - 1; 
    // r: uppointer + 1 = next r position,
    //g: uppointer,
    //b: uppointer
    while ( gp <= bp){ //process from 0 to left, by using gp;
        if ( input[gp] == 'R'){
            MySwap(gp, rp, input);
            rp++;
            gp++;
        }
        else if ( input[gp] == 'G'){
            gp++;
        }
        else if ( input[gp] == 'B'){
           MySwap(gp, bp, input);
           bp--;
        }
    }
    cout <<"Segregated Color: "<<endl;
    MyPrint(input, len);
}
int main() {

    //char input[] = {'G', 'B', 'R', 'R', 'B', 'R', 'G'};
    char input[] = {'B', 'R', 'R', 'B', 'R', 'G', 'R', 'G','G'};
    int len = sizeof(input)/sizeof(input[0]);
    cout <<"Input Color: "<<endl;
    MyPrint(input, len);
    SegregateColor(input, len);
    return 0;
}
