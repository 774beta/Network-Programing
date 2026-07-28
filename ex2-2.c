#include <stdio.h>
int main(){
// 1. ポインタ変数の宣言
char c, *cp;
int i, *ip;
double d, *dp;

// 2. ポインタ変数の演算
cp = &c;
printf("cp = %p, cp+1 = %p, cp+2 = %p\n", cp, cp+1, cp+2);
// 制御文字 %p は 16進アドレス表示を指定
ip = &i;
printf("ip = %p, ip+1 = %p, ip+2 = %p\n", ip, ip+1, ip+2);
dp = &d;
printf("dp = %p, dp+1 = %p, dp+2 = %p\n", dp, dp+1, dp+2);
}