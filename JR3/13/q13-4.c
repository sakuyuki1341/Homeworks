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

void change_color(struct rb_node *t, int color) {
	if(t == NULL) {
		// nop
	} else {
		t->black = color;
	}
}

///
/// 二分探索木tにおいて、根の子と孫に現れる赤親子を回転と色変えによって解消し、
/// 解消後の根のアドレスを返す関数
///
struct rb_node* resolve_red_pair(struct rb_node *t) {
	//根がNULLの時の処理
	if(t == NULL) {
		return NULL;
	}

	// Caseの分類
	//それぞれの位置が赤であれば1そうでなければ0
	int left = 0, right = 0, left_left = 0, left_right = 0, right_left = 0, 
		right_right = 0;
	if(t->left != NULL) {
		left = is_red(t->left);
		left_left = is_red(t->left->left);
		left_right = is_red(t->left->right);
	}
	if(t->right != NULL) {
		right = is_red(t->right);
		right_left = is_red(t->right->left);
		right_right = is_red(t->right->right);
	}

	// Case1
	if(left == 1 && left_left == 1) {
		// Case1.1
		if(right == 1) {
			change_color(t, 0);
			change_color(t->left, 1);
			change_color(t->right, 1);
		// Case1.2
		} else {
			t = rotate_right(t);
			change_color(t, 1);
			change_color(t->right, 0);
		}
	}

	// Case2
	if(left == 1 && left_right == 1) {
		// Case2.1
		if(right == 1) {
			change_color(t, 0);
			change_color(t->left, 1);
			change_color(t->right, 1);
		// Case2.2
		} else {
			t->left = rotate_left(t->left);
			t = rotate_right(t);
			change_color(t, 1);
			change_color(t->right, 0);
		}
	}

	// Case3
	if(right == 1 && right_left == 1) {
		// Case3.1
		if(left == 1) {
			change_color(t, 0);
			change_color(t->left, 1);
			change_color(t->right, 1);
		// Case3.2
		} else {
			t->right = rotate_right(t->right);
			t = rotate_left(t);
			change_color(t, 1);
			change_color(t->left, 0);
		}
	}

	// Case4
	if(right == 1 && right_right == 1) {
		// Case4.1
		if(left == 1) {
			change_color(t, 0);
			change_color(t->left, 1);
			change_color(t->right, 1);
		// Case4.2
		} else {
			t = rotate_left(t);
			change_color(t, 1);
			change_color(t->left, 0);
		}
	}
	return t;
}

///
/// 赤黒木tに対し値dを挿入し、赤親子を解消し、根のアドレスを返す関数
///
struct rb_node* rb_insert_rec(struct rb_node *t, struct student d) {
	if(t == NULL) {
		struct rb_node* new = (struct rb_node*)malloc(sizeof(struct rb_node));
		new->left = NULL;	new->right = NULL;
		new->data = d;
		new->black = 0;
		return new;
	} else {
		if(d.id < t->data.id) {
			t->left = rb_insert_rec(t->left, d);
		} else if(d.id > t->data.id) {
			t->right = rb_insert_rec(t->right, d);
		}
		return resolve_red_pair(t);
	}
}

///
/// rb_insert_secの呼び出し関数
///
struct rb_node* rb_insert(struct rb_node *t, struct student d) {
	t = rb_insert_rec(t, d);
	t->black = 1;
	return t;
}

///
/// メイン関数
///
int main() {
	struct student d;
	struct rb_node *t = NULL;
	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		sscanf(buf, "%d,%[^,],%d", &d.id, d.name, &d.score);
		t = rb_insert(t, d);
	}
	print_rbtree(t);
	return 0;
}