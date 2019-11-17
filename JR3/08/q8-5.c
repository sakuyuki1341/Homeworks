/************************************************
 * マクロ部
 ************************************************/

#include <stdio.h>
#include <stdlib.h>

/************************************************
 * グローバル変数
 ************************************************/

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
/// 配列aのm番目からn番目の要素についてm番目の要素より小さいものを前に
/// 大きいものを後ろに移す. なお番目は0番目を最初とする.
///
int partition(struct point a[], int m, int n) {
	int randnum = m + rand()%(n-m+1);
	struct point pivot = a[randnum];	//ランダムな番目をpivotに入れる
	//pivotの位置をm番目と交換
	struct point tmp = a[randnum];
	a[randnum] = a[m];
	a[m] = tmp;
	int l = m+1;
	int r = n;
	while(1) {
		// lがnより左にあり、l番目の要素がpivotより小さい時、lを右に移す
		while(l < n && compare(a[l], pivot) == -1) {
			l++;
		}
		// rがmより右にあり、r番目の要素がpivotより大きい時、rを左に移す
		while(r > m && compare(a[r], pivot) == 1) {
			r--;
		}
		// lがrより左にアレばl番目とr番目を交換
		if(l < r) {
			tmp = a[l];
			a[l] = a[r];
			a[r] = tmp;
		} else {	//そうでなければ繰り返しを終了
			break;
		}
		l++;
		r--;
	}
	// a[r]とa[m]を交換
	a[m] = a[r];
	a[r] = pivot;

	return r;
}

///
/// 配列aのm番目からn番目までを、クイックソートアルゴリズムにより、指定された基準で昇順に整列する関数
///
void quicksort(struct point a[], int m, int n) {
	// mがnより小さい時
	if(m < n) {
		int p = partition(a, m, n);
		quicksort(a, m, p-1);
		quicksort(a, p+1, n);
	}	//そうでなければ何もしない
}

///
/// メイン関数
///
int main() {
	char buf[128];	// １行分の入力保存
	struct point p, arr[128];	// 入力の保存
	int i = 0, n;
	scanf("%c ", &kijun);	// 規準の読み込み
	// 座標の入力
	while(fgets(buf, sizeof(buf), stdin) != NULL && i < 128) {
		sscanf(buf, "%d %d", &p.x, &p.y);
		arr[i] = p;
		++i;
	}
	n = i;
	// ソート実行
	quicksort(arr, 0, n-1);
	// 整列結果を表示
	for(i = 0; i < n; ++i)
		printf("%d %d\n", arr[i].x, arr[i].y);
	return 0;
}