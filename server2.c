#include <stdio.h>
#include <stdlib.h>
#include <string.h> // strlen()
#include <fcntl.h> // open(), creat()
#include <unistd.h> // read(), write(), close()
#define PIPE "/tmp/mypipe" // 1.
// 名前付きパイプの指定
int main(){
char buf[80];
int fd;
fd = open(PIPE, O_WRONLY); // 2.
if (fd == -1){
fprintf(stderr, "PIPE does not exist! \n");
exit(1);
}
while(1) {
    memset(buf, '\0', sizeof(buf));
    scanf("%s", buf);
    write(fd, buf, strlen(buf)); // 3.

    if(strcmp(buf, "Takano")==0) {
        break;
    }
}
close(fd); // 4.
}