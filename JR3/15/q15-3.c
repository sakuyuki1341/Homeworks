/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>

#define SETMAX 10600	// 集合の要素数の最大値(駅の数)

/************************************************
 * グローバル変数
 ************************************************/
char buf[256];

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
/// アドレスpの指す構造体setが表す集合から最も小さい要素を削除し、
/// その要素を返す関数
///
int delete_min_int(struct set *p) {
	int ret = -1;
	if(p->size == 0) {
		//nop
	} else {
		int min = p->elements[0];
		int min_num = 0;
		for(int i = 0; i < p->size; i++) {
			if(min > p->elements[i]) {
				min = p->elements[i];
				min_num = i;
			}
		}
		p->elements[min_num] = p->elements[p->size - 1];
		p->size -= 1;
		ret = min;
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
	i = 0;
	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		sscanf(buf, "%d ", &s.elements[i]);	//入力された整数値を集合sに格納
		++i;	//添字を1つ増やす
	}
	s.size = i;	//この時点でiに要素の数が格納されている
	while(1) {
		m = delete_min_int(&s);
		if(m < 0)	break;	//mが負なら集合がからなので終了
		printf("%d : ", m); print_set(&s);	//最小値と集合を出力
	}
}