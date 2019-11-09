/************************************************
 * マクロ部
/************************************************/
#include <stdio.h>

/************************************************
 * 構造体等宣言部
/************************************************/
struct point { int x, y; };	//座標構造体

/************************************************
 * グローバル変数
 ************************************************/

/************************************************
 * プロトタイプ宣言部
/************************************************/

/************************************************
 * 関数部
/************************************************/
///
/// 座標p1, p2に対し、文字cで指定された基準で比較した結果を「1, 0, -1」として返す
/// p1がp2より大きい場合: 1 / p1とp2が等しい場合: 0 / p1がp2より小さい場合: -1
///
int compare_by(struct point p1, struct point p2, char c) {
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
/// メイン関数
///
int main(int argc, char const *argv[]) {
	char c, buf[128];	//入力保存用
	struct point p, arr[128];	//入力保存用
	int i = 0;
	//基準取得
	scanf("%c ", &c);
	//座標取得
	while(fgets(buf, sizeof(buf), stdin) != NULL && i < 128) {
		sscanf(buf, "%d %d", &p.x, &p.y);
		arr[i] = p;
		++i;
	}
	//最大の座標の表示
	printf("%d\n", max_index_by(arr, i, c));
	return 0;
}