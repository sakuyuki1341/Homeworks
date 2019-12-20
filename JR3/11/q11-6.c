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
	struct node *x, *y, *z;
	char lr;
	//該当の節点の探索し、zへ入れる
	x = t; y = NULL;
	while(x != NULL) {
		y = x;
		if(id < x->data.id) {
			x = x->left;
			lr = 'l';
		} else if(id > x->data.id){
			x = x->right;
			lr = 'r';
		} else {
			z = x;
			break;
		}
	}
	//削除実行
	if(z->left == NULL && z->right == NULL) {
		y->left = NULL;
		y->right = NULL;
	} else if(z->left == NULL) {
		if(lr == 'r') {
			y->right = z->right;
		} else if(lr == 'l') {
			y->left = z->right;
		}
	} else if(z->right == NULL) {
		if(lr == 'r') {
			y->right = z->left;
		} else if(lr == 'l') {
			y->left = z->left;
		}
	} else if(z->right != NULL && z->left != NULL) {
		struct node* z_parents = y;
		//idより一つ大きいidを探す
		x = t; y = NULL;
		while(x != NULL) {
			y = x;
			if(id+1 < x->data.id) {
				x = x->left;
				lr = 'l';
			} else if(id+1 > x->data.id){
				x = x->right;
				lr = 'r';
			} else {
				z = x;
				break;
			}
		}
		if(x != NULL) {
			y = x;
		}
		//この時、y のdataが一つ大きいid
		
	}
	free((void*)z);
	return t;
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