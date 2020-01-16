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
/// tを根とする二分探索木について、
/// 左右の部分木がAVL木であり、それらの高さの差が2以下である時、
/// 全体としてAVL木になるように変形し、その根のアドレスを返す関数
///
struct avl_node* balance(struct avl_node *t) {
	//左の木の高さ - 右の木の高さ
	int height_diff = height(t->left) - height(t->right);
	struct avl_node* root = t;	//返り値用

	// 左右の部分木の高さの差が1以下
	if(-1 <= height_diff && height_diff <= 1) {
		//nop

	// 左の部分木の高さが右の部分木の高さより2大きい場合
	} else if(height_diff == 2) {
		int height_t1 = height(t->left->left), height_t2 = height(t->left->right);
		if(height_t1 >= height_t2) {
			root = rotate_right(t);
		} else if(height_t2 > height_t1) {
			t->left = rotate_left(t->left);
			root = rotate_right(t);
		}

	// 右の部分木の高さが左の部分木の高さより2大きい場合
	} else if(height_diff == -2) {
		int height_t1 = height(t->right->right), height_t2 = height(t->right->left);
		if(height_t1 >= height_t2) {
			root = rotate_left(t);
		} else if(height_t2 > height_t1) {
			t->right = rotate_right(t->right);
			root = rotate_left(t);
		}
	}

	return root;
}

///
/// tの指す節点を根とするAVL木に、dを挿入してAVL木の条件を満たすように調整し、
/// 挿入後の根の節点のアドレスを返す関数
///
struct avl_node* avl_insert(struct avl_node *t, struct student d) {
	if(t == NULL) {
		struct avl_node* root = (struct avl_node*)malloc(sizeof(struct avl_node));
		root->data = d;
		root->right = NULL; root->left = NULL;
		root->height = 1;
		return root;
	} else if(t != NULL) {
		if(d.id < t->data.id) {
			t->left = avl_insert(t->left, d);
		} else if(d.id > t->data.id) {
			t->right = avl_insert(t->right, d);
		}
	}
	put_height(t);
	return balance(t);
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
	struct student st;
	struct avl_node *t = NULL;
	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		//学生の情報を読み取り
		sscanf(buf, "%d,%[^,],%d", &st.id, st.name, &st.score);
		//AVL木にそのデータを追加
		t = avl_insert(t, st);
	}
	print_avl(t);
	return 0;
}