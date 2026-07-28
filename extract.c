#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *method;
    char *query_string = NULL;
    char buf[256];
    
    // 1. ブラウザ表示のおまじない
    printf("Content-type: text/html\n\n");
    printf("<pre>\n");

    // 2. GET/POSTの判定
    method = getenv("REQUEST_METHOD");

    if (method != NULL) {
        if (strcmp(method, "GET") == 0) {
            // GETの場合は環境変数から取得
            query_string = getenv("QUERY_STRING");
        } else if (strcmp(method, "POST") == 0) {
            // POSTの場合は標準入力から取得
            scanf("%s", buf);
            query_string = buf;
        }

        // 3. 文字列の分割と抽出
        if (query_string != NULL) {
            // "=" で文字列を分割
            char *key = strtok(query_string, "=");
            char *value = strtok(NULL, "=");

            if (value != NULL) {
                // POSTの際にスペースが '+' に置換される対策
                for(int i = 0; value[i] != '\0'; i++) {
                    if(value[i] == '+') value[i] = ' ';
                }
                // 抽出した入力値のみを表示
                printf("%s\n", value);
            }
        }
    }

    printf("</pre>\n");
    return 0;
}