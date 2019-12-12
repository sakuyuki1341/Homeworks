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
struct student { char name[32]; int score; };	//学生

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
/// 既に登録されている名前がある場合、スコアを足し合わせる
///
void set_data(struct node *table[], struct student st) {
	int hash_num = hash(st.name);
	//存在するか検索
	int find_flag = 0;
	struct node* move_node = table[hash_num];
	while(move_node != NULL) {
		if(strcmp(move_node->data.name, st.name) == 0) {
			find_flag = 1;
			break;
		}
		move_node = move_node->next;
	}
	//登録もしくはスコアの更新
	if(find_flag == 0) {
		//ノードの確保
		struct node* node_new = (struct node*)malloc(sizeof(struct node));
		node_new->data = st;
		node_new->next = NULL;
		//登録作業
		move_node = table[hash_num];
		if(move_node == NULL) {
			table[hash_num] = node_new;
		} else {
			while(move_node->next != NULL) {
				move_node = move_node->next;
			}
			move_node->next = node_new;
		}
	} else {
		move_node->data.score += st.score;
	}
}

///
/// メイン関数
///
int main() {
	int i, score_tmp;
	char buf[128];
	struct student st;
	struct node *table[SIZE], *p;
	//ハッシュ表の配列の各要素をNULLで初期化
	for(i=0; i<SIZE; ++i) table[i] = NULL;
	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		sscanf(buf, "%[^,],%d", st.name, &st.score);
		set_data(table, st);	//ハッシュ表に st を登録
	}
	for(i=0; i<SIZE; ++i) {
		p = table[i];
		while(p != NULL) {
			st = p->data;
			printf("%d,%s,%d\n", i, st.name, st.score);
			p = p->next;
		}
	}
	return 0;
}