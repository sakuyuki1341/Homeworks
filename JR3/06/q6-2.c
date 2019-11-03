/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define DIGITS 126
#define ANS 252

/************************************************
 * 構造体等宣言部
 ************************************************/

/************************************************
 * グローバル変数
 ************************************************/
char buf[DIGITS + 2];   //標準入力用

/************************************************
 * プロトタイプ宣言部
 ************************************************/
//配列arrのi番目の数を繰り上げを行う関数
void carry(int* arr, int i);

/************************************************
 * 関数部
 ************************************************/
///
/// メイン関数
///
int main() {
    int i, j, len1, len2, len_ans;
    int arr1[DIGITS] = {}, arr2[DIGITS] = {};   //数値保存用
    int arr_ans[ANS] = {};  //回答用
    //標準入力一行目
    i = 0;
    fgets(buf, sizeof(buf), stdin);
    while(buf[i] != '\n') {
        i++;
    }
    len1 = i;
    for(i = 0; i < len1; i++) {
        arr1[i] = (int)(buf[len1 - 1 - i] - '0');
    }

    //標準入力二行目
    i = 0;
    fgets(buf, sizeof(buf), stdin);
    while(buf[i] != '\n') {
        i++;
    }
    len2 = i;
    for(i = 0; i < len2; i++) {
        arr2[i] = (int)(buf[len2 - 1 - i] - '0');
    }

    //掛け算実行
    for(i = 0; i < len2; i++) {
        for(j = 0; j < len1; j++) {
            arr_ans[i+j] += arr1[j] * arr2[i];
        }
    }

    //各桁に対して繰り上がりの処理
    for(i = 0; i < ANS; i++) {
        carry(arr_ans, i);
    }

    //arr_ansの最大桁がいくつかを探す
    for(i = ANS - 1; i >= 0; i--) {
        if(arr_ans[i] != 0) {
            len_ans = i + 1;
            break;
        }
    }

    //arr_ansの表示
    for(i = len_ans - 1; i >= 0; i--) {
        printf("%d", arr_ans[i]);
    }
    printf("\n");

    return 0;
}

 void carry(int* arr, int i) {
     while(arr[i] >= 10) {
         if(arr[i] >= 10000) {
             arr[i+4] += 1;
             arr[i] -= 10000;
         } else if(arr[i] >= 1000) {
             arr[i+3] += 1;
             arr[i] -= 1000;
         } else if(arr[i] >= 100) {
             arr[i+2] += 1;
             arr[i] -= 100;
         } else if(arr[i] >= 10) {
             arr[i+1] += 1;
             arr[i] -= 10;
         }
     }
 }
