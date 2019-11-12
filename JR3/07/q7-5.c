/************************************************
 * マクロ部
/************************************************/
#include <stdio.h>

/************************************************
 * グローバル変数
 ************************************************/
int count = 0;	//比較回数

/************************************************
 * 構造体等宣言部
/************************************************/
struct point { int x, y; };

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
/// 配列aの先頭n-1個が文字cの基準で昇順に整列されている時
/// a[n-1]を適切な位置に移動して、aが昇順に整列された状態にする
///
void insert_by(struct point a[], int n, char c) {
	int insert_place = 0;	//a[n-1]が挿入されるべき位置
	//挿入位置の探索
	for(int i = n-2; i >= 0; i--) {
		if(compare_by(a[n-1], a[i], c) >= 0) {	//一時最大値の更新
			insert_place = i + 1;
			break;
		}
	}
	//挿入処理
	for(int i = insert_place; i < n - 1; i++) {
		struct point tmp = a[i];
		a[i] = a[n-1];
		a[n-1] = tmp;
	}
}

///
///	配列aのうち、先頭n個について、文字cの基準で昇順に整列する
///
void insertion_sort(struct point a[], int n, char c) {
	//kを2からnまでずらしながら繰り返し
	for(int k = 2; k <= n; k++) {
		insert_by(a, k, c);
	}
}

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
	insertion_sort(arr, n, c);
	//比較回数の出力
	printf("%d\n", count);
	//配列の要素の出力
	for(i = 0; i < n; ++i) {
		printf("%d %d\n", arr[i].x, arr[i].y);
	}
	return 0;
}