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
/// t の指す節点を根とする二分探索木から、学籍番号がidと一致する学生の
/// 節点を削除し、得られた二分探索木の根のアドレスを返す関数
///
struct node* bst_delete(struct node *t, int id) {
	struct node *root = t;
	// 削除対象が左部分木に存在する場合、そこから削除
	if(id < root->data.id) {
		root->left = bst_delete(root->left, id);
	// 削除対象が右部分木に存在する場合、そこから削除
	} else if(id > root->data.id) {
		root->right = bst_delete(root->right, id);
	// 削除対象が自身の時、自身を削除
	} else {
		struct node *n = t, *x, *y;
		//削除実行
		if(n->right == NULL) {
			root = n->left;
		} else if(n->right->left == NULL) {
			n->right->left = n->left;
			root = n->right;
		} else {
			x = n->right;
			y = NULL;
			while(x->left != NULL) {
				y = x;
				x = x->left;
			}
			y->left = NULL;
			x->left = n->left;
			x->right = n->right;
			root = x;
		}
		free(n);
		return root;
	}
}

///
/// メイン関数
///
int main() {
	struct node *t = get_tree();
	int id;
	scanf("%d ", &id);
	t = bst_delete(t, id);
	print_bst(t);
	return 0;
}