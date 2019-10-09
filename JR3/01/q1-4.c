/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************
 * 関数部
 ************************************************/
// メイン関数
int main(void) {
    char input[128];    // 入力保存用
    fgets(input, 128, stdin);
    // 入力された数を変数に格納
    int x = atoi(strtok(input, " "));
    int y = atoi(strtok(NULL, " "));
    // 最大公約数を計算
    int gcd = 0;    // 最大公約数
    for(int i = 1; i <= x && i <= y; i++) {
        if(x % i == 0 && y % i == 0) {
            gcd = i;
        }
    }
    printf("%d\n", gcd);    // 表示
    return 0;
}
