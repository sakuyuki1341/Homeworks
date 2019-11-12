/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>

/************************************************
 * 構造体等宣言部
 ************************************************/

//座標構造体
typedef struct point {
	 int x, y;
} point;

/************************************************
 * グローバル変数
 ************************************************/

int count = 0;	//比較回数

/************************************************
 * プロトタイプ宣言部
 ************************************************/

int compare_by(point p1, point p2, char c);
void bubble_sort(struct point a[], int n, char c);

/************************************************
 * 関数部
 ************************************************/
///
/// メイン関数
///
int main(int argc, char const *argv[]) {
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
	bubble_sort(arr, n, c);	//比較
	//比較回数の出力
	printf("%d\n", count);
	//配列の要素の出力
	for(i = 0; i < n; ++i) {
		printf("%d %d\n", arr[i].x, arr[i].y);
	}
	return 0;
}

///
/// 座標p1, p2に対し、文字cで指定された基準で比較した結果を「1, 0, -1」として返す
/// p1がp2より大きい場合: 1 / p1とp2が等しい場合: 0 / p1がp2より小さい場合: -1
///
int compare_by(point p1, point p2, char c) {
	count++;
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
///	配列aのうち、先頭n個について、文字cで指定された基準で昇順に整列する
///
void bubble_sort(struct point a[], int n, char c) {
	//kをn-2から0までずらしながら繰り返し
	for(int k = n-2; k >= 0; k--) {
		//lを0からkまでずらしながら繰り返し
		for(int l = 0; l <= k; l++) {
			//a[l]がa[l+1]より大きい場合交換
			if(compare_by(a[l], a[l+1], c) > 0) {
				point tmp = a[l];
				a[l] = a[l+1];
				a[l+1] = tmp;
			}
		}
	}
}