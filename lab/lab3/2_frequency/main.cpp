#include <iostream>
#include <stdio.h>

int values[120];
/* 20 based, ascii 20-126,
//107: whitespace characters,
//108: other characters(ascii<20, >126)
//109: '\t'
//110:'\n'
*/

void count(char cur){
    int key = cur - ' ';
    if (cur == ' ')
        values[107]++;
    else if (cur == '\t')
        {key = 107;}
    else if (cur == '\n')
        {key = 107;}
    else if ( cur > 126 || cur < 20)
        key = 108;
    values[key]++;
}
void printcount(){
    //if (values[109] > 0) printf("\'\\t\' %d\n",values[109]);
    //if (values[110] > 0) printf("\'\\n\' %d\n",values[110]);
    for (int i = 0; i <= 106; i++){
        if (values[i] > 0)
            printf("\'%c\' %d\n",(i+' '),values[i]);
    }
    if (values[107] > 0) printf("whitespace characters %d\n",values[107]);
    if (values[108] > 0) printf("other characters %d",values[108]);  
}
int main(int argc, char** argv){
    FILE *fp = fopen(argv[1],"r");
    char cur;
    while ( (cur = fgetc(fp)) != EOF){
        count(cur);
    }
    fclose(fp);
    printcount();
    return 0;
}