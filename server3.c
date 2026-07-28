#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen()
#include <fcntl.h> // open(), creat()
#include <unistd.h> // read(), write(), close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// 名前付きパイプの指定
int main() {
    int sockfd_s, sockfd_c; // 要求待機のためのソケット識別子
    sockfd_s = socket(AF_INET, SOCK_STREAM, 0); // socket() の実行

    struct sockaddr_in address_s; // サーバソケットのアドレス構造体
    // アドレス構造体への代入
    address_s.sin_family = AF_INET; // IPv4の使用
    address_s.sin_addr.s_addr = inet_addr("127.0.0.1"); // サーバのIPアドレス指定
    address_s.sin_port = htons(50000); // ポート番号指定
    // bind()の実行
    bind(sockfd_s, (struct sockaddr *)&address_s, sizeof(address_s));

    listen(sockfd_s, 5);
    printf("server waits \n");

    struct sockaddr_in address_c; // クライアント接続用ソケットのアドレス構造体
    unsigned int length_c = sizeof(address_c); // アドレス構造体のサイズ初期化
    // ↓ 要求受付とクライアントの確認
    sockfd_c = accept(sockfd_s,(struct sockaddr *)&address_c, &length_c);
    printf("\n * request from client IP: %s, port: %d\n",
        inet_ntoa(address_c.sin_addr), ntohs(address_c.sin_port));

char buf[80]="\0";
memset(buf, '\0', sizeof(buf)); // buf[]読み込み前に初期化
 read(sockfd_c, buf, sizeof(buf));
 printf("\n * message from client : %s \n", buf);
// クライアントへのデータ送信
strcpy(buf, "From Server via socket"); // 送信データのbuf[]への設定
 write(sockfd_c, buf, strlen(buf));

close(sockfd_c); // 名前なしソケットの除去
close(sockfd_s); // 名前付きソケットの除去
return 0;
}