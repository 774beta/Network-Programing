#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid;

    // パイプの作成
    if (pipe(fd) < 0) {
        perror("pipe error");
        exit(1);
    }

    // プロセスの生成
    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(1);
    }

    if (pid == 0) {
        // --- 子プロセス側の処理 (ls -l の実行) ---
        // 1. 不要な「パイプ入力」を閉じる
        close(fd[0]);
        // 2. 一旦「標準出力」を閉じる
        close(1);
        // 3. 「パイプ出力」を標準出力(fd=1)にコピー
        dup(fd[1]);
        // 4. コピー元の「パイプ出力」を閉じる
        close(fd[1]);

        // ls -l の実行
        execl("/bin/ls", "ls", "-l", NULL);
        perror("execl ls error");
        exit(1);
    } else {
        // --- 親プロセス側の処理 (grep put の実行) ---
        // 1. 不要な「パイプ出力」を閉じる
        close(fd[1]);
        // 2. 一旦「標準入力」を閉じる
        close(0);
        // 3. 「パイプ入力」を標準入力(fd=0)にコピー
        dup(fd[0]);
        // 4. コピー元の「パイプ入力」を閉じる
        close(fd[0]);

        // grep put の実行
        execl("/bin/grep", "grep", "put", NULL);
        perror("execl grep error");
        exit(1);
    }

    return 0;
}