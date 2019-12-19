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
typedef int datatype;
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
		sscanf(buf, "%d ", &t->data);	// buf から読み込み、data へ保存
		t->left = get_tree();	//左の子の節点から下の木を生成
		t->right = get_tree();	//右の子の節点から下の木を生成
		return t;
	}
}

///
/// t の指す節点を根とする二分木に含まれる節点の数を返す関数
///
int size(struct node *t) {
	int ret_num = 0;
	if(t == NULL) {
		//nop
	} else {
		//左右の size に自分の分を足す
		ret_num = size(t->left) + size(t->right) + 1; 
	}
	return ret_num;
}

///
/// t の指す節点を根とする二分木の高さを返す関数
///
int height(struct node *t) {
	int ret_num = 0;
	if(t == NULL) {
		// nop
	} else {
		//左右の高さを取得
		int left_height = height(t->left);
		int right_height = height(t->right);
		//比較
		if(left_height > right_height) {
			ret_num = left_height + 1;
		} else {
			ret_num = right_height + 1;
		}
	}
	return ret_num;
}

///
/// t の指す節点を根とする二分木に含まれる節点のデータの合計を返す関数
///
int sum(struct node *t) {
	int ret_num = 0;
	if(t == NULL) {
		// nop
	} else {
		//左右の sum と自分の data を足し合わせる
		ret_num = sum(t->left) + sum(t->right) + t->data;
	}
	return ret_num;
}

///
/// メイン関数
///
int main() {
	struct node *t = get_tree();
	printf("%d\n", size(t));
	printf("%d\n", height(t));
	printf("%d\n", sum(t));
	return 0;
}