/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>

/************************************************
 * グローバル変数
 ************************************************/
int count = 0;	//比較回数
char kijun;	//比較規準

/************************************************
 * 構造体等宣言部
 ************************************************/
struct point { int x, y; };	//座標

/************************************************
 * プロトタイプ宣言部
 ************************************************/

/************************************************
 * 関数部
 ************************************************/
///
/// 座標p1, p2に対し、文字kijunで指定された基準で比較した結果を「1, 0, -1」として返す
/// p1がp2より大きい場合: 1 / p1とp2が等しい場合: 0 / p1がp2より小さい場合: -1
///
int compare(struct point p1, struct point p2) {
	++count;
	int ret = 0;
	if(kijun == 'X') {	//基準がXの時
		if(p1.x > p2.x) {
			ret = 1;
		} else if(p1.x < p2.x) {
			ret = -1;
		} else {
			if(p1.y > p2.y) {
				ret = 1;
			} else if(p1.y < p2.y) {
				ret = -1;
			} else {
				ret = 0;
			}
		}
	}
	if(kijun == 'Y') {	//基準がYの時
		if(p1.y > p2.y) {
			ret = 1;
		} else if(p1.y < p2.y) {
			ret = -1;
		} else {
			if(p1.x > p2.x) {
				ret = 1;
			} else if(p1.x < p2.x) {
				ret = -1;
			} else {
				ret = 0;
			}
		}
	}
	if(kijun == 'D') {	//基準がDの時
		if(p1.x*p1.x + p1.y*p1.y > p2.x*p2.x + p2.y*p2.y) {
			ret = 1;
		} else if(p1.x*p1.x + p1.y*p1.y < p2.x*p2.x + p2.y*p2.y) {
			ret = -1;
		} else {
			if(p1.x > p2.x) {
				ret = 1;
			} else if(p1.x < p2.x) {
				ret = -1;
			} else {
				if(p1.y > p2.y) {
					ret = 1;
				} else if(p1.y < p2.y) {
					ret = -1;
				} else {
					ret = 0;
				}
			}
		}
	}
	return ret;
}

///
/// 配列aについて,m+1番目からn番目までがヒープの条件を満たしているときに
/// m番目の要素を適切な位置に挿入してm番目からn番目までがヒープの条件を
/// 満たしているようにする関数
///
void pushdown(struct point a[], int m, int n) {
	int i = 0;
	if(2*m + 1 > n) {
		return;
	}
	if(2*m + 1 == n) {
		//比較入れ替え
		if(compare(a[2*m+1], a[m]) == 1) {
			struct point tmp = a[2*m+1];
			a[2*m+1] = a[m];
			a[m] = tmp;
		}
		return;
	}
	if(2*m + 2 <= n) {
		if(compare(a[2*m+1], a[2*m+2]) == 1) {
			i = 2*m + 1;
		} else {
			i = 2*m + 2;
		}
		//比較入れ替え
		if(compare(a[i], a[m]) == 1) {
			struct point tmp = a[i];
			a[i] = a[m];
			a[m] = tmp;
			pushdown(a, i, n);
		}
		return;
	}
	return;
}

///
/// 配列aの先頭n個の要素を、ヒープソートアルゴリズムにより、
/// 指定された規準で昇順に整列する関数
///
void heap_sort(struct point a[], int n) {
	//ヒープ作成
	for(int k = n/2 - 1; k >= 0; k--) {
		pushdown(a, k, n-1);
	}
	//ヒープから取り出し
	for(int k = n-1; k >= 1; k--) {
		//0番目とk番目を交換
		struct point tmp = a[0];
		a[0] = a[k];
		a[k] = tmp;
		//関数pushdownで、0番目の要素を1番目からk-1番目のヒープに押し込む
		pushdown(a, 0, k-1);
	}
}

///
///	メイン関数
///
int main() {
	char buf[128];
	struct point p, arr[128];
	int i = 0, n;
	scanf("%c ", &kijun);
	while(fgets(buf, sizeof(buf), stdin) != NULL && i < 128) {
		sscanf(buf, "%d %d", &p.x, &p.y);
		arr[i] = p;
		++i;
	}
	n = i;
	heap_sort(arr, n);
	printf("%d\n", count);
	for(i=0;i<n;++i)
		printf("%d %d\n", arr[i].x, arr[i].y);
	return 0;
}
