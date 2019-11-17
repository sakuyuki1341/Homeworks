/************************************************
 * マクロ部
 ************************************************/

#include <stdio.h>
#include <stdlib.h>

/************************************************
 * グローバル変数
 ************************************************/

int count = 0;	//比較回数
char kijun;	//大小比較の規準を表す

/************************************************
 * 構造体等宣言部
 ************************************************/

struct point { int x, y; };	//座標
typedef struct point elementtype;

struct node { elementtype element ; struct node *next; };
typedef struct node* list;

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
/// l1に与えられた連結リストを分割し、分割した結果を
/// l1とl2の指す接点を頭とする連結リストに格納する.
///
void split(list l1, list l2) {
	list p1 = l1, p2 = l1;
	while(p2->next->next != NULL && p2->next != NULL) {
		p2 = p2->next->next;
		p1 = p1->next;
	}
	l2 = p1->next;
	p1->next = NULL;
}

///
/// 昇順に整列された連結リストl1, l2に対し、
/// それらを併合した連結リストl1に格納する.
///
void merge(list l1, list l2) {
	while(l1->next != NULL) {
		l1 = l1->next;
	}
	l1->next = l2;
}

///
/// 連結リストを指定された規準で昇順に整列する.
///
void merge_sort(list l) {
	
}


///
/// メイン関数
///
int main() {
	char buf[128];	// １行分の入力保存
	struct point p;	// 入力の保存
	list l, last;	// 入力の保存
	scanf("%c ", &kijun);	// 規準の読み込み
	// 座標の入力
	last = l = (list)malloc(sizeof(struct node));
	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		sscanf(buf, "%d %d", &p.x, &p.y);
		last = last->next = (list)malloc(sizeof(struct node));
		last->element = p;
	}
	last->next = NULL;
	// ソート実行
	merge_sort(l);
	// 整列結果を表示
	printf("%d\n", count);
	while((l=l->next) != NULL) {
		p = l->element;
		printf("%d %d\n", p.x, p.y);
	}
	return 0;
}
