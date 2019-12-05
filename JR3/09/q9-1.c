/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>

/************************************************
 * グローバル変数
 ************************************************/
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
///	構造体pointを要素に持つ配列aのうち、先頭n個がヒープになっていれば
///	1を返し、ヒープでなければ0を返す関数
///
int is_heap(struct point a[], int n) {
	int heaped = 1;	//ヒープされているかどうか
	int i;
	//2*i+1 と 2*i+2 番目を調べる
	for(i = 0; 2*i + 2 < n; i++) {
		if(compare(a[i], a[2*i + 1]) < 0 || compare(a[i], a[2*i + 2]) < 0) {
			heaped = 0;
		}
	}
	//2*i+1番目を再確認
	if(2*i + 1 < n) {
		if(compare(a[i], a[2*i + 1]) < 0) {
			heaped = 0;
		}
	}
	return heaped;
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
	if(is_heap(arr, n)) printf("Yes.\n");	/*関数is_heapが1を返せばYes.を出力*/
	else printf("No.\n");					/*0を返せばNo.を出力*/
	return 0;
}
