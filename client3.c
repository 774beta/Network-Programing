#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen()
#include <fcntl.h> // open(), creat()
#include <unistd.h> // read(), write(), close()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PIPE "/tmp/mypipe" // 1.
// 名前付きパイプの指定

int main(){
    int sockfd; // 要求のためのソケット識別子
    int res;
    struct sockaddr_in address; // クライアントソケットのアドレス構造体

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // サーバIP
    address.sin_port = htons(50000); // サーバポート

    res = connect(sockfd, (struct sockaddr *)&address, sizeof(address));
    if(res == -1){ // 接続要求失敗時は、強制終了
        perror("接続エラー\n"); 
        exit(1);
    }
    printf("\n * server IP: %s, port: %d\n", // サーバ情報の確認
        inet_ntoa(address.sin_addr), ntohs(address.sin_port));

        char buf[80] = "\0";
        strcpy(buf, "client will connect to server");
        write(sockfd, buf, strlen(buf));
        // サーバからのデータ受信
        memset(buf, '\0', sizeof(buf)); // buf[]読み込み前に初期化
        read(sockfd, buf, sizeof(buf));
        printf("\n * message from server : %s \n", buf);

close(sockfd); // 4.
return 0;
}