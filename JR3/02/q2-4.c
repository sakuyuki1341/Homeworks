/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/************************************************
 * プロトタイプ宣言部
 ************************************************/
bool* primer(int count);

/************************************************
 * グローバル変数
 ************************************************/
bool is_prime[1024];

/************************************************
 * 関数部
 ************************************************/
// メイン関数
int main(void) {
    char input[1024];    // 入力保存用
    // 入力
    fgets(input, 1024, stdin);
    int input_len = strlen(input);
    // 素数の計算
    bool* p_num = primer(input_len);
    for (int i = 0; i < input_len; i++) {
        if(p_num[i+1]) {
            printf("%c", input[i]);
        }
    }
    return 0;
}

bool* primer(int count) {
    is_prime[0] = false;
    bool i_is_prime_num = false;
    for(int i = 2; i < count; i++) {
        i_is_prime_num = true;
        for(int j = 2; j < i; j++) {
            if(i % j == 0) {
                i_is_prime_num = false;
                break;
            }
        }
        if(i_is_prime_num) {
            is_prime[i] = true;
        } else {
            is_prime[i] = false;
        }
    }
    return is_prime;
}
