/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define DIGITS 126

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

/************************************************
 * 関数部
 ************************************************/
///
/// メイン関数
///
int main() {
	int i, len1, len2;
	int arr1[DIGITS] = {}, arr2[DIGITS] = {};   //数値保存及び足し算用
	//標準入力一行目
	i = 0;
	fgets(buf, sizeof(buf), stdin);
	printf("%s\n", buf);
	while(buf[i] != '\n') {
		++i;
	}
	len1 = i;
	printf("%d\n", len1);
	for(i = 0; i < len1; ++i) {
		arr1[i] = (int)(buf[len1-1-i]-'0');
	}

	//標準入力二行目
	i = 0;
	fgets(buf, sizeof(buf), stdin);
	printf("%s\n", buf);
	while(buf[i] != '\n') {
		++i;
	}
	len2 = i;
	printf("%d\n", len2);
	for(i = 0; i < len2; ++i) {
		arr2[i] = (int)(buf[len2-1-i]-'0');
	}

	for(i=len1-1; i >= 0; --i) {
		printf("%d", arr1[i]);
	}
	printf("\n");
	for(i=len2-1; i >= 0; --i) {
		printf("%d", arr2[i]);
	}
	printf("\n");

	//足し算実行
	//桁数の少ない方を桁数の多い方へ足し合わせる
	if(len1 > len2) {
		for(i = 0; i < len2; i++) {
			arr1[i] += arr2[i];
		}
		for(i = 0; i < len1; i++) { //繰り上がりの処理
			if(arr1[i] >= 10) {
				arr1[i] -= 10;
				arr1[i+1] += 1;
			}
		}
		if(arr1[len1] != 0) {   //最大桁が増えている場合
			len1 += 1;
		}
		for(i = len1 - 1; i >= 0; i--) {
			printf("%d", arr1[i]);
		}
		printf("\n");
	} else {
		for(i = 0; i < len1; i++) {
			arr2[i] += arr1[i];
		}
		for(i = 0; i < len2; i++) { //繰り上がりの処理
			if(arr2[i] >= 10) {
				arr2[i] -= 10;
				arr2[i+1] += 1;
			}
		}
		if(arr2[len2] != 0) {   //最大桁が増えている場合
			len2 += 1;
		}
		for(i = len2 - 1; i >= 0; i--) {
			printf("%d", arr2[i]);
		}
		printf("\n");
	}
	return 0;
}
