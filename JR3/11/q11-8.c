/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>

/************************************************
 * グローバル変数
 ************************************************/
char buf[128];	//get_treeで用いる

/************************************************
 * 構造体等宣言部
 ************************************************/
struct student { int id; char name[32]; int score; };
typedef struct student datatype;
struct node { datatype data; struct node *left, *right; };


/************************************************
 * プロトタイプ宣言部
 ************************************************/

/************************************************
 * 関数部
 ************************************************/
///
/// tの指す節点を根とする二分探索木に、dをメンバdataとする節点を追加する関数
///
void bst_insert(struct node *t, struct student d) {
	struct node *dummy = t->left;
	struct node *x = t->right, *y = dummy;
	struct node *node_new = (struct node*)malloc(sizeof(struct node));
	node_new->data = d;
	node_new->left = dummy;
	node_new->right = dummy;
	while(x != dummy) {
		y = x;
		if(d.id < x->data.id) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	if(y == dummy) {
		t->right = node_new;
	} else if(d.id < y->data.id) {
		y->left = node_new;
	} else {
		y->right = node_new;
	}
}

///
/// 葉がダミーになった二分探索木を出力する関数
///
void print_bst_dummy(struct node *t, struct node *dummy) {
	if(t == dummy) 
		printf(".\n");
	else {
		printf("%d,%s,%d\n", t->data.id, t->data.name, t->data.score);
		print_bst_dummy(t->left, dummy);
		print_bst_dummy(t->right, dummy);
	}
	return;
}

///
/// 葉がダミーになった頭付きの二分探索木を出力する関数
///
void print_bst(struct node *t) {
	print_bst_dummy(t->right, t->left);
	return;
}

///
/// t の指す節点を根とする二分探索木の中から、学籍番号が id と一致する
/// 学生の名前と成績をカンマで区切った文字列を標準出力に出力する関数
///
void find_info(struct node *t, int id) {
	//ダミー節点のデータに目的の学籍番号を代入
	t->left->data.id = id;
	struct node *x = t->right, *y;
	while(1) {
		if(x->data.id > id) {
			x = x->left;
		} else if(x->data.id < id) {
			x = x->right;
		} else if(x->data.id == id) {
			if(x->left != x) {
				printf("%s,%d", x->data.name, x->data.score);
			} else {
				printf("Not found.");
			}
			break;
		}
	}
}

///
/// メイン関数
///
int main() {
	char buf[128], c;
	int id;
	struct node *t = (struct node*)malloc(sizeof(struct node)),
				*dummy = (struct node*)malloc(sizeof(struct node));
	struct student st;
	t->left = t->right = dummy->left = dummy->right = dummy;
	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		sscanf(buf, "%d%c", &id, &c);
		if(c == ',') {
			sscanf(buf, "%d,%[^,],%d", &st.id, st.name, &st.score);
			//二分探索木にデータを追加
			bst_insert(t, st);
		}
	}
	print_bst(t);
	find_info(t, id);
	return 0;
}