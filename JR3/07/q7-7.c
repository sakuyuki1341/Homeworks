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
//添字情報を含む構造体
struct point_loc { int loc; struct point p; };
typedef struct point_loc point_loc;

/************************************************
 * グローバル変数
 ************************************************/

/************************************************
 * プロトタイプ宣言部
 ************************************************/

int compare_by(point_loc p1, point_loc p2, char c);
void stable_selection_sort(struct point a[], int n, char c);

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
	stable_selection_sort(arr, n, c);	//比較
	//配列の要素の出力
	for(i = 0; i < n; ++i) {
		printf("%d %d\n", arr[i].x, arr[i].y);
	}
	return 0;
}

///
/// 座標p1, p2に対し、文字cで指定された基準で比較した結果を「1, -1」として返す
/// p1がp2より大きい場合: 1 / p1がp2より小さい場合: -1
///
int compare_by(point_loc p1, point_loc p2, char c) {
	int ret = 0;
	if(c == 'x') {	//基準がxの時
		if(p1.p.x > p2.p.x) {
			ret = 1;
		} else if(p1.p.x < p2.p.x) {
			ret = -1;
		} else {
			if(p1.loc > p2.loc) {
				ret = 1;
			} else if(p1.loc < p2.loc) {
				ret = -1;
			}
		}
	}
	if(c == 'y') {	//基準がyの時
		if(p1.p.y > p2.p.y) {
			ret = 1;
		} else if(p1.p.y < p2.p.y) {
			ret = -1;
		} else {
			if(p1.loc > p2.loc) {
				ret = 1;
			} else if(p1.loc < p2.loc) {
				ret = -1;
			}
		}
	}
	if(c == 'd') {	//基準がdの時
		if(p1.p.x*p1.p.x + p1.p.y*p1.p.y > p2.p.x*p2.p.x + p2.p.y*p2.p.y) {
			ret = 1;
		} else if(p1.p.x*p1.p.x + p1.p.y*p1.p.y < p2.p.x*p2.p.x + p2.p.y*p2.p.y) {
			ret = -1;
		} else {
			if(p1.loc > p2.loc) {
				ret = 1;
			} else if(p1.loc < p2.loc) {
				ret = -1;
			}
		}
	}
	return ret;
}

///
///	配列aのうち、先頭n個について、文字cで指定された基準で昇順に整列する
///
void stable_selection_sort(struct point a[], int n, char c) {
	struct point_loc arr[128];	//配列の用意
	//元の配列aの各要素に適切な添字情報を付けたものをarrに格納する
	for(int i = 0; i < n; i++) {
		arr[i].loc = i;
		arr[i].p = a[i];
	}
	//kをnから2まで1ずつ減らしながら繰り返し
	for(int k = n; k > 1; k--) {
		// 最大値の取得
		int max_place = 0;	//最大値の位置
		//k個まで繰り返し
		for(int i = 1; i < k; i++) {
			if(compare_by(arr[i], arr[max_place], c) >= 0) {	//一時最大値の更新
				max_place = i;
			}
		}

		//i番目とk-1番目を交換
		point_loc tmp = arr[k-1];
		arr[k-1] = arr[max_place];
		arr[max_place] = tmp;
	}

	for(int i = 0; i < n; i++) {
		a[i] = arr[i].p;
	}
	
}