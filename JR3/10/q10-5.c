/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
/// ハッシュ表に登録されている要素のうち、メンバnameがsであるような学生の得点を返す
///
int find_score(struct node *table[], char *s) {
	int hash_num = hash(s);	//sのハッシュ値
	int ret_score = -1;	//返すスコア
	struct node* move_node = table[hash_num];
	while(move_node != NULL) {
		if(strcmp(move_node->data.name, s) == 0) {
			ret_score = move_node->data.score;
			break;
		}
		move_node = move_node->next;
	}
	return ret_score;
}

///
/// メイン関数
///
int main() {
	int i, v;
	char buf[128], name[32];
	struct student st;
	struct node *table[SIZE];

	//ハッシュ表の配列の各要素をNULLで初期化
	for(i=0; i<SIZE; ++i) table[i] = NULL;
	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		sscanf(buf, "%d,", &v);
		//各行の最初の数値によって分岐
		if(v > 0) {
			sscanf(buf, "%d,%[^,],%d", &st.id, st.name, &st.score);
			set_data(table, st);	//ハッシュ表に st を登録
		} else
			sscanf(buf, "0,%[^,\n]", name);
	}
	v = find_score(table, name);
	if(v < 0) printf("Not found.\n");
	else      printf("%d\n", v);
	return 0;
}