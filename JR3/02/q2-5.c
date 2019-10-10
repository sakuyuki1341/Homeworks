/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXLINE 256  // 一行の最大長
#define MAXCOLM 256  // 行数の最大値

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
    char buf[MAXLINE];
    while(fgets(buf, sizeof(buf), stdin) != NULL) { // 取得し続ける
        int mem[MAXLINE];   // 行の数字保存配列
        char *p = buf;
        int tmp, count = 0;
        // 分割
        while(sscanf(p, "%d", &tmp) != EOF) {
            mem[count++] = tmp;
            p = strchr(p, ' ');
            if(p == NULL) break;
            else while(*p == ' ') ++p;
        } 
        //表示
        for(int i = 0, j = 0; i < count; j++) {
            if(mem[i] == j) {
                printf("#");
                i++;
            } else {
                printf(" ");
            }
        }
        printf("\n");   // 後処理
    }
}