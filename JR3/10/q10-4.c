/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 101

/************************************************
 * グローバル変数
 ************************************************/

/************************************************
 * 構造体等宣言部
 ************************************************/
struct student { int id; char name[32]; int score; };	//学生

struct node { struct student data; struct node *next; };

/************************************************
 * プロトタイプ宣言部
 ************************************************/

/************************************************
 * 関数部
 ************************************************/
///
/// 文字列sを128進数とみなしてSIZEで割ったあまりを計算する関数
///
int hash(char *s) {
	int tmp = s[0] % SIZE;
	for(int i = 1; i < 32 && s[i] != '\0'; i++) {
		tmp = (tmp * 128 + s[i]) % SIZE;
	}
	return tmp;
}

///
/// ハッシュ表tableに、stを登録する関数
///
void set_data(struct node *table[], struct student st) {
	int hash_num = hash(st.name);
	//ノードの確保
	struct node* node_new = (struct node*)malloc(sizeof(struct node));
	node_new->data = st;
	node_new->next = table[hash_num];
	//登録作業
	table[hash_num] = node_new;
}

///
/// メイン関数
///
int main() {
	int i;
	char buf[128];
	struct student st;
	struct node *table[SIZE], *p;
	//ハッシュ表の配列の各要素をNULLで初期化
	for(i=0; i<SIZE; ++i) table[i] = NULL;
	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		sscanf(buf, "%d,%[^,],%d", &st.id, st.name, &st.score);
		set_data(table, st);	//ハッシュ表に st を登録
	}
	for(i=0; i<SIZE; ++i) {
		p = table[i];
		while(p != NULL) {
			st = p->data;
			printf("(%d)%d,%s,%d\n", i, st.id, st.name, st.score);
			p = p->next;
		}
	}
	return 0;
}