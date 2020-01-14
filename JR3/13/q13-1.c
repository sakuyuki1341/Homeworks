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
struct rb_node { datatype data; struct rb_node *left, *right; int black; };

/************************************************
 * プロトタイプ宣言部
 ************************************************/

/************************************************
 * 関数部
 ************************************************/
///
/// 標準入力から与えられた文字列を元に赤黒木を作る関数
///
struct rb_node* get_rbtree() {
	struct rb_node *t;
	char c;
	//ドットだけならNULLを返す
	if(fgets(buf, sizeof(buf), stdin) == NULL || buf[0] == '.')
		return NULL;
	else {
		//ドットでなければ節点を表す構造体のアドレスtを用意
		t = (struct rb_node*)malloc(sizeof(struct rb_node));
		//色を表す文字をcに、学籍番号、名前、得点をt->dataに格納
		sscanf(buf, "[%c]%d,%[^,],%d", &c, &t->data.id, t->data.name, &t->data.score);
		//色の文字がbなら1,rなら0
		t->black = (c=='b');
		//左の子をt->leftに、右の子をt->rightに格納
		t->left = get_rbtree(); t->right = get_rbtree();
		//tを返す
		return t;
	}
}

///
/// tの指す節点が赤であれば1を、黒でああれば0を返す関数
///
int is_red(struct rb_node *t) {
	return (t != NULL && !t->black);
}

///
/// tの指す節点を根とする二分探索木に対して右回転を行い、
/// その根のアドレスを返す関数
///
struct rb_node* rotate_right(struct rb_node *t) {
	struct rb_node *root = t;
	if(t == NULL) {
		// nop
	} else if(t->left == NULL) {
		// nop
	} else {
		root = t->left;
		t->left = root->right;
		root->right = t;
	}
	return root;
}

///
/// tの指す節点を根とする二分探索木に対して左回転を行い、
/// その根のアドレスを返す関数
///
struct rb_node* rotate_left(struct rb_node *t) {
	struct rb_node *root = t;
	if(t == NULL) {
		// nop
	} else if(t->right == NULL) {
		// nop
	} else {
		root = t->right;
		t->right = root->left;
		root->left = t;
	}
	return root;
}

///
/// 赤黒木から入力と同じ形式に戻し、出力する関数
///
void print_rbtree(struct rb_node *t) {
	if(t == NULL) printf(".\n");
	else {
		printf("[%c]%d,%s,%d\n", t->black ? 'b' : 'r', t->data.id, t->data.name, t->data.score);
		print_rbtree(t->left); print_rbtree(t->right);
	}
}

///
/// メイン関数
///
int main() {
	struct rb_node *t;
	char c;
	scanf("%c ", &c);
	t = get_rbtree();
	if(c == 'R') t = rotate_right(t);		//Rなら右回転
	else if(c == 'L') t = rotate_left(t);	//Lなら左回転
	print_rbtree(t);
	return 0;
}