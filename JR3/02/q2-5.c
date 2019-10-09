/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXLINE 128  // 一行の最大長
#define MAXCOLM 80  // 行数の最大値

/************************************************
 * プロトタイプ宣言部
 ************************************************/

/************************************************
 * グローバル変数
 ************************************************/

/************************************************
 * 関数部
 ************************************************/
// メイン関数
int main(void) {
    // 入力保存用
    char buf[MAXCOLM][MAXLINE + 2];
    int mem[MAXCOLM][MAXLINE]; // 数字用
    int i, j;
    int x_len[MAXCOLM]; // 各行の長さ
    int mem_x_num[MAXLINE]; // 数字の個数

    // 入力
    for(i = 0; fgets(buf[i], sizeof(buf[i]), stdin) != NULL; i++) {
        // 分割
        char* tmp = strtok(buf[i], " ");
        if(strcmp(tmp, "\n") == 0 || tmp == NULL) {
            mem_x_num[i] = 0;
            continue;
        }
        mem[i][0] = atoi(tmp);
        for(j = 1;; j++) {
            char* tmp = strtok(NULL, " ");
            if(tmp == NULL) {
                break;
            } else {
                mem[i][j] = atoi(tmp);
            }
        }
        x_len[i] = mem[i][j-1];
        mem_x_num[i] = j;
        int count = 0;
        
        // 表示
        for(int j = 0; j <= x_len[i]; j++) {
            if(count >= mem_x_num[i]) {
                printf("\n");
                count = 0;
            } else if(mem[i][count] == j) {
                printf("%c", '#');
                count++;
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
