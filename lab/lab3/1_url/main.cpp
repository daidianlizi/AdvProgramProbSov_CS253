#include <stdio.h>
#include <iostream>
using namespace std;

#define MAX_LENGTH 2083
char cururl[MAX_LENGTH];
char keys[6][30] = {"scheme","domain","port","path","query_string","fragment_id"};
char myres[6][MAX_LENGTH];

//initial state
int curstate = 0;
int curindex[2] = {0,0};   
int values[6][2] = {{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1},{-1,-1}};
void reset(){
    curstate = 0;
    curindex[0] = 0;   
    for (int i = 0; i < 6; i++){
        values[i][0] = -1;
        values[i][1] = -1;
    }
}
char* myNUrl(int k, int start, int end){
    int l = 0;
    int i = start;
    while (i < end) {
        myres[k][l++] = cururl[i++];
    }
    myres[k][l]='\0';
    return myres[k];
}
void checkStateTrans(char* url, int &i){
    if ((curstate == 0) && (url[i] == ':') && (url[i+1] == '/') && (url[i+2] == '/')){
        values[curstate][0] = 0;
        values[curstate][1] = i;
        //cout<<values[curstate][0]<<values[curstate][1]<<i<<endl;
        curindex[0] = i+3;
        curstate = 1;      
    }//initially, case 1
    else if ((curstate == 0) && (url[i] == ':') ){
        curstate = 1;
        values[curstate][0] = 0;
        values[curstate][1] = i;
        curindex[0] = i+1;
        curstate = 2;
    }//initially, case 2
    else if ((curstate == 0) && (url[i] == '/') ){
        curstate = 1;
        values[curstate][0] = 0;
        values[curstate][1] = i;
        curindex[0] = i+1;
        curstate = 3;
    }//initially, case 3
    else if ((curstate == 1) && (url[i] == ':') ){
        values[curstate][0] = curindex[0];
        values[curstate][1] = i;
        curindex[0] = i+1;
        curstate = 2;
    }// from case 1, case 4
    else if ((curstate == 2) && (url[i] == '/') ){
        values[curstate][0] = curindex[0];
        values[curstate][1] = i;
        curindex[0] = i+1;
        curstate = 3;
    }// from case 2/4, case 5
    else if ((curstate == 3) && (url[i] == '?') ){
        values[curstate][0] = curindex[0];
        values[curstate][1] = i;
        curindex[0] = i+1;
        curstate = 4;
    }// from case 3/5, case 6
    else if ((curstate == 4) && (url[i] == '#') ){
        values[curstate][0] = curindex[0];
        values[curstate][1] = i;
        curindex[0] = i+1;
        curstate = 5;
    }// from case 6, case 7
}
void parseUrl(char* url){
    int i = 0;
    //process and state trans
    while ( url[i] != '\0'){
        i++;
        checkStateTrans(url,i);  
    }
    //last state
    values[curstate][0] = curindex[0];
    values[curstate][1] = i;
    for (int k = 0; k < 6; k ++){
        //cout<<values[k][0]<<values[k][1];
        if ((values[k][1] - values[k][0]) > 0)
            //printf("\033[1m%s: \033[0m%s\n",keys[k],myNUrl(k,values[k][0],values[k][1]));
            printf("%s: %s\n",keys[k],myNUrl(k,values[k][0],values[k][1]));
        //can be optimized to O(1) space
    }
}
int main(){
    while( scanf("%s",cururl) != EOF) {
        reset();
        parseUrl(cururl);
        printf("<blank line>\n");
    }
    return 0;
}