#include <iostream> 
#define STRMAX 100
using namespace std;

void lineParse(char* line){
	char single_ele, pre_elem;
	int i = 0;
	while ( (single_ele = line[i]) != '\0'){
		i++;
		switch(single_ele){
			case ' ':
			case '\t':
			case '\n':
				if (pre_elem != '\n' )
					cout << '\n';
				pre_elem = '\n';
				break;
			case '<':
			case '>':
			case '&':
			case '|':
				cout << '\n' << single_ele << '\n';
				pre_elem = '\n';
				break;
			default:
				cout << single_ele;
				pre_elem = single_ele;
			}
		}
}
int main(){
	char line[STRMAX];
	while (cin.getline(line,STRMAX)){
		lineParse(line);
	}
} 