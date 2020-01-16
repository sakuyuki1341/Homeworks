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
///	二分探索木tに対して、左右の赤黒木の黒の節点の通る数を返す関数
///
int is_rbtree_rec(struct rb_node *t) {
	//条件2の確認
	if(is_red(t)) {
		if(is_red(t->left) || is_red(t->right)) {
//			printf("fault 2nd conditions\n");
			return 0;
		}
	}
	//条件3の確認
	if(t == NULL) {
		return 1;
	} else {
		int black_num_left = is_rbtree_rec(t->left),
			black_num_right = is_rbtree_rec(t->right);
		if(black_num_left == 0 || black_num_right == 0) {
			return 0;
		}
		if(black_num_left != black_num_right) {
//			printf("fault 3rd conditions\n");
			return 0;
		} else if(is_red(t)) {
			return black_num_right;
		} else {
			return black_num_right + 1;
		}
	}
}

///
/// 二分探索木tに対して、赤黒木であれば1を返し、そうでなければ0を返す関数
///
int is_rbtree(struct rb_node *t) {
	int ret = is_rbtree_rec(t);
//	printf("ret = %d\n", ret);
	if(ret > 1) {
		ret = 1;
	}
	return ret;
}

///
/// メイン関数
///
int main() {
	struct rb_node *t = get_rbtree();
	if(is_rbtree(t))	printf("Yes.\n");
	else				printf("No.\n");
	return 0;
}