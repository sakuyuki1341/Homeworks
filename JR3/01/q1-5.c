/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************
 * 関数部
 ************************************************/
int main(void) {
    char input[128];    // 入力保存用
    fgets(input, 128, stdin);
    int first = 0, second = 0, tmp = 0; // 順に一番目、二番目、一時保存用
    first = atoi(strtok(input, " "));
    // 一番目、二番目を順に更新
    for(int i = 1; i < 10; i++) {
        tmp = atoi(strtok(NULL, " "));
        if(first < tmp) {
            second = first;
            first = tmp;
        } else if(second < tmp) {
            second = tmp;
        }
    }
    printf("%d\n", second);    // 二番目を表示
    return 0;
}
