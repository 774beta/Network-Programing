#include <stdio.h>
#include <stdlib.h>
struct student {
    char id[10]; // 学籍番号
    int score; // 評点
};
int main() {
    struct student seito[10]; // 学生情報格納配列
    int count=0;
    int sum=0;
    double avg;
    FILE *fin, *fout;                   // ファイルポインタを定義

    fin = fopen("input2.dat", "r");     // 入力ファイル
    if (fin==NULL) {
        printf("No file\n");
        exit(1);
    }

    fout = fopen("output.dat","w");    // 出力ファイル
    if (fout==NULL) {
        printf("Cannot open output file\n");
        fclose(fin);
        exit(1);
    }

    while(fscanf(fin, "%s %d", seito[count].id, &seito[count].score) != EOF) {
        sum+=seito[count].score;
        count++;
    }           // ～終了まで繰返
    

    if(count>0) {
        avg=sum/count;
        fprintf(fout,"%d\n", count);
        fprintf(fout, "%.2f\n", avg);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
