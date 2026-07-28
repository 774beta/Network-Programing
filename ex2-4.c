#include <stdio.h>
void slink(char*s, char *arg1, char *arg2);
int main(int argc, char *argv[]){
    char s[30];
    int i;
    slink(s, argv[1], argv[2]);
    printf("%s\n", s);          // 引数(文字列)を表示
}

void slink(char *s, char *s1, char *s2) {
    int i=0;
    while(*s1 !='\0') {
        s[i]=*s1;
        i++; s1++;
    }

    s[i]='_';
    i++;

     while(*s2 !='\0') {
        s[i]=*s2;
        i++; s2++;
    }
    s[i]='\0';
}
