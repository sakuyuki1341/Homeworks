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
typedef char datatype;
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
		sscanf(buf, "%c ", &t->data);	// buf から読み込み、data へ保存
		t->left = get_tree();	//左の子の節点から下の木を生成
		t->right = get_tree();	//右の子の節点から下の木を生成
		return t;
	}
}

///
/// t の指す節点を根とする二分木の各節点のデータを行きがけ順に標準出力する関数
///
void print_preorder(struct node *t) {
	if(t == NULL) {
		// nop
	} else {
		printf("%c", t->data);
		print_preorder(t->left);
		print_preorder(t->right);
	}
}

///
/// t の指す節点を根とする二分木の各節点のデータを通りがけ順に標準出力する関数
///
void print_inorder(struct node *t) {
	if(t == NULL) {
		// nop
	} else {
		print_inorder(t->left);
		printf("%c", t->data);
		print_inorder(t->right);
	}
}

///
/// t の指す節点を根とする二分木の各節点のデータを帰りがけ順に標準出力する関数
///
void print_postorder(struct node *t) {
	if(t == NULL) {
		// nop
	} else {
		print_postorder(t->left);
		print_postorder(t->right);
		printf("%c", t->data);
	}
}

///
/// メイン関数
///
int main() {
	struct node *t = get_tree();
	print_preorder(t);	printf("\n");
	print_inorder(t);	printf("\n");
	print_postorder(t);	printf("\n");
	return 0;
}