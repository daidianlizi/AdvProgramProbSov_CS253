#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

int main () {
   char str[80] = "This is - www.tutorialspoint.com - website";
   const char s[2] = "-";
   char *token;
   
   /* get the first token */
   token = strtok(str, s);
   
   /* walk through other tokens */
   while( token != NULL ) {
      printf( " %s\n", token );
      cout<<"str|"<<str<<"|,s|"<<s<<"|"<<NULL<<endl;   
      token = strtok(NULL, s);
   }
   
   return(0);
}
