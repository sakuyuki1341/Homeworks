/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************
 * プロトタイプ宣言部
 ************************************************/
int cmb(int n, int k);

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
    // 組合せの数を計算
    int ans = cmb(x, y);
    printf("%d", ans);  // 表示
    return 0;
}

// 組合せ計算
int cmb(int n_max, int k_max) {
    int nck[n_max+1][k_max+1];  // 組合せの配列確保
    // 計算
    for(int n = 0; n <= n_max; n++) {
        for(int k = 0; k <= k_max && k <= n; k++) {
            if(k == 0 || k == n) {
                nck[n][k] = 1;
            } else {
                nck[n][k] = nck[n-1][k] % 2718 + nck[n-1][k-1] % 2718;
            }
        }
    }
    return nck[n_max][k_max] % 2718;    // 余りを戻す
}
