/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************
 * プロトタイプ宣言部
 ************************************************/
int power(int n, int k);

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
    // 所定の計算
    int ans = power(x, y);
    printf("%d", ans);  // 表示
    return 0;
}

// 累乗計算
int power(int n, int k) {
    if(k == 1) {    // n^(1)のときnを2718で割った余りを返す
        return n % 2718;
    } else if(k % 2 == 1) { // kが奇数のとき
        return power(n, k-1) % 2718 * n % 2718; // n^kとnをそれぞれ2718で割った余りを返す
    } else if(k % 2 == 0) { // kが偶数のとき
        int tmp = power(n, k/2) % 2718; // 一時保存
        return (tmp*tmp) % 2718;    // n^kを2718で割った余りの二乗を返す
    } else {    // デフォルト
        return 0;
    }
}
