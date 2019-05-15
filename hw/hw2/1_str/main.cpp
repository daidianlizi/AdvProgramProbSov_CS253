#include <stdio.h>
#define require(e) if (!(e)) fprintf(stderr, "FAILED line %d        %s: %s       %s\n", __LINE__, __FILE__, __func__, #e)


int strlen(const char* s){
    int len = 0;
    while(s[len] != '\0')
        len++;
    return len;
}
int strncmp(const char* s1, const char* s2, int k){
    for (int i = 0; i < k ; i++){
        if (s1[i] == s2[i]) 
            continue;
        else 
            return (s1[i] - s2[i]);
    }
    return 0;
}
int strcmp(const char* s1, const char* s2){
    int k = strlen(s1) < strlen(s2)? strlen(s1) : strlen(s2); //min
    return strncmp(s1, s2, k+1);
}
char* strcpy(char* dest, char* src){
    char* head = dest;
    char* cur = src;
    while ((*(head++) = *(cur++)) != '\0')
        ;
    return dest;
}
char* strcat(char* dest, const char* src){
    char* head = dest;
    int endofdest = strlen(dest);
    dest = dest + endofdest;
    while ( (*(dest++) = *(src++)) != '\0' )
        ;
    return head;
}
char* strchr(char* src, char c){
    for(int i = 0; src[i]; i++){
        if (src[i] == c)
            return src+i;
    }
    return nullptr;
}
char* strstr(char* hay, const char* needle){
    int len = strlen(needle); //O(n)
    char* p = hay;
    while (p[0] != '\0'){
        p = strchr(p, needle[0]); // O(m)
        if (p == nullptr)
            return nullptr;
        else if ( strncmp(hay, needle, len) == 0 ) // O(n)
            return p;
        else 
            p = p+1;
    }
    return nullptr;
}
char* strpbrk(char* dest, char* src){
    char *p = dest, *res = dest;
    while (p[0] != '\0'){
        res = strchr(src,p[0]);
        if (res != nullptr)
            return p;
        else p = p+1;
    }
    return nullptr;
}
int strspn(char* dest, char* src){
    int res = 0;
    char *p = dest;
    while (p[0] != '\0'){
        if ( strchr(src,p[0]) != nullptr )
            res++;
        p = p+1;
    }
    return res;
}
char* strtok(char* str, const char* delimiter){
    static char* left = NULL;//stored in static storage, for later caller. allocated before main
    if(str == NULL)
        str = left;
    if(str == NULL)
        return NULL;

    const char *p;
    bool flag;
    //remove the redundant delimiters in the start
    while( *str != '\0'){
        p = delimiter;
        flag = false;
        while (*p != '\0'){//judge the cur char
            if (*p++ == *str){
                flag = true;
                break;
            }
        }
        if (!flag)
            break;
        str++;
    }

    if ( *str == '\0')
        return NULL;

    char *s = str; //str to keep the start point
    //find the first delimiters in str
    while( *s != '\0'){
        p = delimiter;
        flag = false;
        while (*p != '\0'){//judge the cur char
            if (*p++ == *s){
                flag = true;
                *s = '\0';
                break;
            }
        }
        ++s;
        if(flag){
            left = s;
            return str;
        }
    }
    left = NULL;
    return str;
}
void test_strlen(){
    require(strlen("") == 0);
    require(strlen("hello") == 5);
}
void test_strcmp(){
    char r[] = "hello", s[] = "hello", t[] = "he";
    require(strcmp(r,s) == 0);
    require(strcmp(t,r) < 0);
    require(strcmp(s,t) > 0);
}
void test_strncmp(){
    char r[] = "hello", s[] = "hello", t[] = "he";
    require(strncmp(r,s,3) == 0);
    require(strncmp(t,s,4) < 0);
    require(strncmp(s,t,4) > 0);
}
void test_strcpy(){
    char r[1024] = "hello", s[1024] = "world", t[1024] = "he";
    require( strcmp(strcpy(r,s), "world") == 0);
    require( strcmp(strcpy(t,s), "world") == 0);
    t[0] = 'h', t[1] = 'e', t[2] = '\0';
    require( strcmp(strcpy(s,t), "he") == 0);
}
void test_strcat(){
    char r[1024] = "hello", s[1024] = "world", t[1024] = "he";
    require( strcmp(strcat(r,s), "helloworld") == 0);
    require( strcmp(strcat(t,r), "hehelloworld") == 0);
    require( strcmp(strcat(s,t), "worldhehelloworld") == 0);
}
void test_strchr(){
    char r[] = "hello", s[] = "world", t[] = "he";
    char tofindc = 'l';
    require( strcmp(strchr(r,tofindc), "llo") == 0);
    require( strcmp(strchr(s,tofindc) , "ld") == 0);
    require( strchr(t,tofindc) == nullptr);
}
void test_strstr(){
    char r[] = "hello", s[] = "world", t[] = "he";
    char tofinds[] = "he";
    require( strcmp(strstr(r,tofinds), "hello") == 0);
    require(strstr(s,tofinds) == nullptr);
    require( strcmp(strstr(t,tofinds), "he") == 0);
}
void test_strpbrk(){
    char r[] = "aaphello", s[] = "world", t[] = "e";
    char tofinds[] = "eh";
    require( strcmp(strpbrk(r,tofinds), "hello") == 0);
    require(strpbrk(s,tofinds) == nullptr);
    require( strcmp(strpbrk(t,tofinds), "e") == 0);
}
void test_strspn(){
    char r[] = "hello", s[] = "world", t[] = "e";
    char tofinds[] = "he";
    require(strspn(r,tofinds) == 2);
    require(strspn(s,tofinds) == 0);
    require(strspn(t,tofinds) == 1);
}
void test_strtok(){
    char s[80] = "This is - www.tutorialspoint.com - website";
    const char todelim[2] = "-";
    char *token; 
    /* get the first token */
    //token = require( strcmp(strtok(s,todelim),"This is ") == 0);  
    token = strtok(s,todelim);
    /* walk through other tokens */
    while( token != NULL ) {
        printf( "%s\n", token ); 
        token = strtok(NULL,todelim);  
    }   
    char t[] ="- This, a sample string.";
    char * pch;
    //pch = require( strcmp(strtok(t," ,.-"),"This") == 0);
    pch = strtok(t," ,.-");
    while (pch != NULL){
        printf ("%s\n",pch);
        pch = strtok(NULL, " ,.-");
    }
}

int main()
{
    test_strlen();
    test_strcmp();
    test_strncmp();
    test_strcpy();
    test_strchr();
    test_strstr();
    test_strcat();
    test_strpbrk();
    test_strspn();
    test_strtok();
    printf("Congratulation! All success!\n");
    return 0;
}
