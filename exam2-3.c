#include <stdio.h>
int main(){
char s[20];
char *cp = "Kyutech";
int i = 0;
while (*cp != '\0'){
s[i] = *cp; // cpが指す文字を一字ずつsへ代入
 i++; cp++; // 配列 s、cp(格納領域)を1進める
 }
s[i] = '\0'; // sの最後に文字列終了文字を代入
 printf("%s\n", s); // %s指定 ～ Kyutech が出力
}