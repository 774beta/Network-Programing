#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char buf[13]; // サイズは13で固定 [cite: 690]
    int fd_in, fd_out;
    ssize_t read_bytes;
    int count = 0;
    int sum = 0;
    int score;
    double average;
    char out_buf[100]; // 出力用のバッファ

    // 入力ファイルのオープン [cite: 201, 245-257]
    fd_in = open("input2.dat", O_RDONLY);
    if (fd_in < 0) {
        perror("open input2.dat");
        exit(1);
    }

    // 出力ファイルのオープン（新規作成、書き込みのみ） [cite: 245-256]
    fd_out = open("output2.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out < 0) {
        perror("open output2.dat");
        close(fd_in);
        exit(1);
    }

    // 13バイトずつ複数回繰り返して読み込む [cite: 688, 690]
    while ((read_bytes = read(fd_in, buf, sizeof(buf))) > 0) {
        // 読み込んだ13文字の文字列から、学籍番号を読み飛ばして(%*s) 評点(%d)だけを取得
        if (sscanf(buf, "%*s %d", &score) == 1) {
            sum += score;
            count++;
        }
        
        // 次の読み込みのためにバッファを初期化 [cite: 207, 208]
        memset(buf, '\0', sizeof(buf));
    }

    // 学生数と平均点の書き込み
    if (count > 0) {
        average = (double)sum / count;
        
        // システムコール write() にはフォーマット出力機能がないため、
        // 一度 sprintf で文字列 (out_buf) に変換してから書き込む
        sprintf(out_buf, "%d\n %.2f\n", count, average);
        write(fd_out, out_buf, strlen(out_buf));
    }

    // ファイルのクローズ [cite: 214, 267-269]
    close(fd_in);
    close(fd_out);

    return 0;
}