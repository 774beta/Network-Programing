#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 階乗計算関数
int fact(int x) {
    if (x <= 1) return 1;
    else return x * fact(x - 1);
}

int main() {
    char *method;
    char *query_string;
    
    printf("Content-type: text/html\n\n");
    printf("<pre>\n");

    method = getenv("REQUEST_METHOD");

    if (method != NULL && strcmp(method, "GET") == 0) {
        query_string = getenv("QUERY_STRING");
        
        if (query_string != NULL) {
            char *key = strtok(query_string, "=");
            char *value = strtok(NULL, "=");

            if (value != NULL) {
                // 抽出した文字列を整数(int)に変換
                int n = atoi(value);
                // 階乗を計算して表示
                printf("%d! = %d\n", n, fact(n));
            }
        }
    }

    printf("</pre>\n");
    return 0;
}