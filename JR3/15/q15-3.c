/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>

#define SETMAX 10600	// 集合の要素数の最大値(駅の数)

/************************************************
 * グローバル変数
 ************************************************/
char buf[256];	//入力された文字列を格納するグローバル変数
//最小要素を見つけるために利用される配列変数dist
int dist[SETMAX] = { 81, 52, 46, 80, 31, 67, 56, 31, 38, 40 };

/************************************************
 * 構造体等宣言部
 ************************************************/
struct set { int elements[SETMAX]; int size; };

/************************************************
 * プロトタイプ宣言部
 ************************************************/

/************************************************
 * 関数部
 ************************************************/
///
/// アドレスpの指す構造体setが表す集合の要素のうち、
/// dist[m]の値が最も小さくなる要素mを削除し、その要素を返す関数
///
int delete_min(struct set *p) {
	int ret = -1;
	if(p->size == 0) {
		//nop
	} else {
		int min = dist[p->elements[0]];
		int min_num = 0;
		for(int i = 0; i < p->size; i++) {
			if(min > dist[p->elements[i]]) {
				min = dist[p->elements[i]];
				min_num = i;
			}
		}
		ret =p->elements[min_num];
		p->elements[min_num] = p->elements[p->size - 1];
		p->size -= 1;
	}
	return ret;
}

///
/// 構造体の要素を出力する関数
///
void print_set(struct set *p) {
	int i;
	printf("{");
	for(i = 0; i < p->size; ++i) printf(" %d", p->elements[i]);
	printf(" }\n");
}

///
/// メイン関数
///
int main() {
	int i, m;
	struct set s;	//入力される整数値を格納する集合
	i = 0;	//添字0から格納していく
	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		sscanf(buf, "%d ", &s.elements[i]);	//入力された整数値を集合sに格納
		++i;	//添字を1つ増やす
	}
	//この時点でiに要素の数が格納されているはず
	s.size = i;
	while(1) {
		m = delete_min(&s);
		if(m < 0)	break;	//mが負なら集合が空なので終了
		printf("%d : ", m);	//見つけた最小要素を出力
		print_set(&s);
	}
	return 0;
}