/************************************************
 * マクロ部
 ************************************************/

#include <stdio.h>

/************************************************
 * グローバル変数
 ************************************************/

int count = 0;	//比較回数
char kijun;	//大小比較の規準を表す

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
/// 配列aについて、前半(m番目からh番目まで)と後半(h+1番目からn番目まで)がそれぞれ昇順に整列されている時
/// それらを組み合わせて全体(m番目の要素からn番目まで)が昇順に整列されている状態にする関数
///
void merge(struct point a[], int m, int n, int h) {
	int front_start = m;
	const int front_end = h, back_end = n;	//前半後半それぞれの終わりの位置
	struct point arr[n+1];	//並べ替え後の配列
	int num = 0;	//並べ替え後の配列のため
	// 元配列の中身がなくなるまで実行
	while(m <= front_end && h+1 <=back_end) {
		// 前半のものが小さいまたは等しい時
		if(compare(a[m], a[h+1]) <= 0) {
			arr[num++] = a[m++];
		} else {	// 後半のものが小さい時
			arr[num++] = a[h+1];
			h++;
		}
	}
	// 残った方を最後に詰める
	while(m <= front_end) {
		arr[num++] = a[m++];
	}
	while(h+1 <= back_end) {
		arr[num++] = a[h+1];
		h++;
	}
	// 並び替え後の配列の中身を元に戻す
	for(int i = 0; i < num; i++, front_start++) {
		a[front_start] = arr[i];
	}
}


///
/// メイン関数
///
int main() {
	char buf[128];	// １行分の入力保存
	struct point p, arr[128];	// 入力の保存
	int i = 0, h, n;
	scanf("%c %d ", &kijun, &h);	// 規準の読み込み
	// 座標の入力
	while(fgets(buf, sizeof(buf), stdin) != NULL && i < 128) {
		sscanf(buf, "%d %d", &p.x, &p.y);
		arr[i] = p;
		++i;
	}
	n = i;
	// ソート実行
	merge(arr, 0, n-1, h);
	// 整列結果を表示
	printf("%d\n", count);
	for(i = 0; i < n; ++i)
		printf("%d %d\n", arr[i].x, arr[i].y);
	return 0;
}
