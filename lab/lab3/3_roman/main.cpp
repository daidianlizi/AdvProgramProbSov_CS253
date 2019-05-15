#include <iostream>
#include <string.h>
#include <stdlib.h>

bool isvalidinput;
int findRomanToInt(char find_char){
    char roman_dict[] = "IVXLCDM";
    int int_dict[] = {1,5,10,50,100,500,1000};   
    int i = 0;
    for (; i < 7; i++){
        if (roman_dict[i] == find_char)
            return int_dict[i];
    }
    //fprintf(stderr,"invalid char in Roman data : %c\n",find_char);
    isvalidinput = false;
    return -10000;
}
int romanToInt(char* input_string){

    int len = strlen(input_string);
    int sum = findRomanToInt(input_string[len-1]);
       for (int i = len - 2; i >= 0; --i) 
       {
          int tmp_i = findRomanToInt(input_string[i]);
          int tmp_i1 = findRomanToInt(input_string[i+1]);
          if ( tmp_i < tmp_i1)
            sum -= tmp_i;
          else
            sum += tmp_i;
       }
       return sum;
}
void printRomanToInt(char* input_string, int res_int){
    printf("%s => %d\n",input_string,res_int);
}
int main(){
    char input_string[50];
    while( scanf("%s",input_string) != EOF){
      isvalidinput = true;
      int res_int = romanToInt(input_string);
      if (isvalidinput == true)
        printRomanToInt(input_string, res_int);
      else 
        printf("invalid input roman number: %s\n", input_string);
    }
    return 0;
}
