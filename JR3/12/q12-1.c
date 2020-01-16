/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>

/************************************************
 * グローバル変数
 ************************************************/
char buf[128];	//get_avlで用いる

/************************************************
 * 構造体等宣言部
 ************************************************/
struct student { int id; char name[32]; int score; };
typedef struct student datatype;
struct avl_node { datatype data; struct avl_node *left, *right; int height; };

/************************************************
 * プロトタイプ宣言部
 ************************************************/

/************************************************
 * 関数部
 ************************************************/
///
/// 与えられたアドレスの高さを知ることができる関数
///
int height(struct avl_node *t) {
	int ret = 0;
	if(t == NULL) {
		// nop
	} else {
		ret = t->height;
	}
	return ret;
}

///
/// 左右の部分木の高さが正しく設定されている際に、heightを適切に設定し直す関数
///
void put_height(struct avl_node *t) {
	int height_left = height(t->left), height_right = height(t->right);
	if(height_left > height_right) {
		t->height = 1 + height_left;
	} else {
		t->height = 1 + height_right;
	}
}

///
/// 標準入力からAVL木を作成する
///
struct avl_node* get_avl() {
	struct avl_node *t;
	//ドットだけならNULLを返す
	if(fgets(buf, sizeof(buf), stdin) == NULL || buf[0] == '.')
		return NULL;
	else {
		//ドットで無ければ節点を表すアドレスtを用意
		t = (struct avl_node*)malloc(sizeof(struct avl_node));
		//高さをt->heightに、学生の情報をt->dataに格納
		sscanf(buf, "[%d]%d,%[^,],%d", &t->height, &t->data.id, t->data.name, &t->data.score);
		//左の子をt->leftに、右の子をt->rightに格納
		t->left = get_avl();
		t->right = get_avl();
		return t;
	}
}

///
/// tの指す節点を根とする二分探索木に対して右回転を行い、その根のアドレスを返す関数
///
struct avl_node* rotate_right(struct avl_node *t) {
	struct avl_node *root = t;
	if(t == NULL) {
		// nop
	} else if(t->left == NULL) {
		// nop
	} else {
		root = t->left;
		t->left = root->right;
		root->right = t;
		put_height(t);
		put_height(root);
	}
	return root;
}

///
/// tの指す節点を根とする二分探索木に対して左回転を行い、その根のアドレスを返す関数
///
struct avl_node* rotate_left(struct avl_node *t) {
	struct avl_node *root = t;
	if(t == NULL) {
		// nop
	} else if(t->right == NULL) {
		// nop
	} else {
		root = t->right;
		t->right = root->left;
		root->left = t;
		put_height(t);
		put_height(root);
	}
	return root;
}

///
/// AVL木を標準出力へ出力
///
void print_avl(struct avl_node *t) {
	if(t == NULL)
		printf(".\n");
	else {
		printf("[%d]%d,%s,%d\n", t->height, t->data.id, t->data.name, t->data.score);
		print_avl(t->left);
		print_avl(t->right);
	}
}

///
/// メイン関数
///
int main() {
	struct avl_node *t;
	char c;
	scanf("%c ", &c);
	t = get_avl();
	if(c == 'R')
		t = rotate_right(t);
	else if(c == 'L')
		t = rotate_left(t);
	print_avl(t);
	return 0;
}