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
/// 標準入力から二分木を生成し、根の節点のアドレスを返す関数
///
struct node* get_tree() {
	struct node *t;
	//標準入力から buf に文字列を読み込み、先頭が . なら葉とみなして NULL を返す
	if(fgets(buf, sizeof(buf), stdin) == NULL || buf[0] == '.')
		return NULL;
	else {
		//先頭が . 以外なら、節点のためのメモリを確保
		t = (struct node*)malloc(sizeof(struct node));
		sscanf(buf, "%d,%[^,],%d", &t->data.id, t->data.name, &t->data.score);	// buf から読み込み、data へ保存
		t->left = get_tree();	//左の子の節点から下の木を生成
		t->right = get_tree();	//右の子の節点から下の木を生成
		return t;
	}
}

///
/// 二分探索木 t に student の値を追加する関数
///
struct node* bst_insert(struct node *t, struct student d) {
	struct node *x = t, *y = NULL;
	struct node *node_new = (struct node*)malloc(sizeof(struct node));
	node_new->data = d;
	node_new->left = NULL;
	node_new->right = NULL;
	while(x != NULL) {
		y = x;
		if(d.id < x->data.id) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	if(y == NULL) {
		return node_new;
	} else if(d.id < y->data.id) {
		y->left = node_new;
	} else {
		y->right = node_new;
	}
	return t;
}

///
/// 二部探索木を出力する関数
///
void print_bst(struct node *t) {
	if(t == NULL) {
		printf(".\n");
	} else {
		printf("%d,%s,%d\n", t->data.id, t->data.name, t->data.score);
		print_bst(t->left);
		print_bst(t->right);
	}
}

///
/// メイン関数
///
int main() {
	struct node *t = get_tree();
	struct student d;
	scanf("%d,%[^,],%d ", &d.id, d.name, &d.score);
	t = bst_insert(t, d);
	print_bst(t);
	return 0;
}