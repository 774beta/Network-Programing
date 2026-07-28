#include <stdio.h>
void slink(char *s, char *s1, char *s2);

int main(int argc, char *argv[]){
    char s[30], s1[]="Takano", s2[]="Aisei"; // s1,s2には自身の「苗字」と「名前」を設定
    slink(s,s1,s2);     // 配列sに” Kawahara_Kenji”と格納
    printf("%s\n", s); //（※ ↑ は半角アンダーバー）
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