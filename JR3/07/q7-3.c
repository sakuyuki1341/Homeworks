/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>

/************************************************
 * グローバル変数
 ************************************************/
int count = 0;

/************************************************
 * 構造体等宣言部
 ************************************************/
struct point { int x, y; };	//座標構造体

/************************************************
 * プロトタイプ宣言部
 ************************************************/

/************************************************
 * 関数部
 ************************************************/
///
/// 座標p1, p2に対し、文字cで指定された基準で比較した結果を「1, 0, -1」として返す
/// p1がp2より大きい場合: 1 / p1とp2が等しい場合: 0 / p1がp2より小さい場合: -1
///
int compare_by(struct point p1, struct point p2, char c) {
	++count;
	int ret = 0;
	if(c == 'X') {	//基準がXの時
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
	if(c == 'Y') {	//基準がYの時
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
	if(c == 'D') {	//基準がDの時
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
/// 配列aに対し、先頭からn個のうち、文字cで指定された基準で最大の要素の添字を返す
///
int max_index_by(struct point a[], int n, char c) {
	int max_place = 0;	//一時最大値の位置
	//n個まで繰り返し
	for(int i = 1; i < n; i++) {
		if(compare_by(a[i], a[max_place], c) >= 0) {	//一時最大値の更新
			max_place = i;
		}
	}
	return max_place;	//最大値の位置を返す
}

///
/// 配列aのうち、先頭n個について、文字cで指定された基準で昇順に整列する
///
void selection_sort(struct point a[], int n, char c) {
	//kをnから2まで1ずつ減らしながら繰り返し
	for(int k = n; k > 1; k--) {
		//先頭k個までの最大値の添字を取得
		int i = max_index_by(a, k, c);
		//i番目とk-1番目を交換
		struct point tmp = a[k-1];
		a[k-1] = a[i];
		a[i] = tmp;
	}
}

///
/// メイン関数
///
int main() {
	char c, buf[128];	//入力保存用
	struct point p, arr[128];	//入力保存用
	int i = 0, n;
	//基準取得
	scanf("%c ", &c);
	//座標取得
	while(fgets(buf, sizeof(buf), stdin) != NULL && i < 128) {
		sscanf(buf, "%d %d", &p.x, &p.y);
		arr[i] = p;
		++i;
	}
	n = i;	//個数の保存
	//ソート実行
	selection_sort(arr, n, c);
	//比較回数出力
	printf("%d\n", count);
	//配列の要素の出力
	for(i = 0; i < n; ++i) {
		printf("%d %d\n", arr[i].x, arr[i].y);
	}
	return 0;
}