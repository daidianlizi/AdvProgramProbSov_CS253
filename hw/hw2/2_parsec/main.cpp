#include <iostream> 
#define STRMAX 100
using namespace std;

char pre_elem;
bool iscomment = false;
bool isstring = false;
int my_count = 0;
void NewlineCout(){
	if (pre_elem != '\n' )
		cout << '\n';
	pre_elem = '\n';	
}
void FirstPosNewlineCoutChar(int i, char currentstate){
	if ( i != 1 && pre_elem != '\n' )
		cout << '\n';
	cout << currentstate << '\n' ;
	pre_elem = '\n';	
}
void NewlineCoutChar(char currentstate){
	if (pre_elem != '\n' )
		cout << '\n';
	cout<< currentstate << '\n' ;
	pre_elem = '\n';
}
bool checkIsCommentStart(char nextstate){
	if (nextstate == '*') 
		return true;
	else 
		return false;
}
void doIsCommentStart(int &i){
	iscomment = true;
	i++;
}
bool checkIsCommentEnd(char nextstate){
	if (nextstate == '/') 
		return true;
	else 
		return false;
}
void doIsCommentEnd(int &i){
	iscomment = false;
	i++;
}
bool checkIsDoubleOperator(char nextstate, char currentstate){
	if (nextstate == currentstate) 
		return true;
	else if ((nextstate == '=') && (currentstate == '+' | currentstate == '-'| currentstate == '*'| currentstate == '/' | currentstate == '>'| currentstate == '<'| currentstate == '!'))
		return true;
	else
		return false;
}
void doIsDoubleOperator(int &i, char nextstate, char currentstate){
	if (pre_elem != '\n' )
		cout << '\n';
	cout<< currentstate << nextstate << '\n' ;
	pre_elem = '\n';
	i++;
}
bool checkIsStringStart(){
	if (isstring == false) 
		return true;
	else
		return false;
}
void doIsStringStart(char currentstate){
	if (pre_elem != '\n' )
		cout << '\n';
	cout << currentstate;
	pre_elem = currentstate;
	isstring = true;
}
void doIsString(char currentstate){
	cout << currentstate;
	pre_elem = currentstate;
}
void checkIsStringEnd(char currentstate){
	if ( (currentstate == '\"') && (pre_elem != '\\') ) {
		//printf("change isstring to false, since cur,pre: %c,%c.\n", currentstate, pre_elem);
		isstring = false;
	}
}

void lineParse(char* line){
	char currentstate;
	int i = 0;
	while ( (currentstate = line[i]) != '\0'){
		i++;
		my_count++;
		//printf("|test %c, %d, %d,%c,%d|\n",currentstate,isstring,iscomment,pre_elem,my_count);
		if (isstring == true){
			checkIsStringEnd(currentstate);
			doIsString(currentstate);
			continue;
		}
		switch(currentstate){	
			case ' ':
			case '\t':
			case '\n':
				NewlineCout(); break;
			//other special symbols (#[]{};:)+().
			case '#':
			case '(':
			case '[':
			case '{':
			case ':':
				FirstPosNewlineCoutChar(i, currentstate);	break;
			case ')':
			case ']':
			case '}':
			case ';':
			case '.':
			case ',':
				NewlineCoutChar(currentstate); break;			
			//operators (+-*/=&|^%!?><~)
			case '+':
			case '-':
			case '=':
			case '&':
			case '|':
			case '^':
			case '%':
			case '!':
			case '?':
			case '<':
			case '>':
			case '~':
				if (checkIsDoubleOperator(line[i], currentstate)){
					doIsDoubleOperator(i, line[i], currentstate);
				}
				else{
					NewlineCoutChar(currentstate);
				}
				break;
			//operator + recognize and discard program comments (/* to */)
			case '/':
				if (checkIsCommentStart(line[i])) {
					doIsCommentStart(i);
				}
				else {
					NewlineCoutChar(currentstate);
				}
				break;
			//operator + recognize and discard program comments (/* to */)
			case '*':
				if (checkIsCommentEnd(line[i])) {
					doIsCommentEnd(i);
				}
				else {
					NewlineCoutChar(currentstate);
				}
				break;
			//string literals (start with a double quote, may contain escapes like \n or \t or \”)
			//printf as a sentence
			case '\"':
				if ( checkIsStringStart() == true){
					doIsStringStart(currentstate);
				}
				break;
			//identifiers (start with an alpha or an underscore), numbers (start with a digit),
			default:
				if (iscomment == 0){
					cout << currentstate;
					pre_elem = currentstate;
				}
			}
		}
}
int main(){
	char line[STRMAX];
	while (cin.getline(line,STRMAX)){
		lineParse(line);
	}
} 