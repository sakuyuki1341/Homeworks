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
/// t の指す節点を根とする二分探索木の中から、学籍番号が id と一致する
/// 学生の名前と成績をカンマで区切った文字列を標準出力に出力する関数
///
void find_info(struct node *t, int id) {
	if(t == NULL) {
		printf("Not found.");
	} else {
		if(t->data.id > id) {
			find_info(t->left, id);
		} else if(t->data.id < id) {
			find_info(t->right, id);
		} else {
			printf("%s,%d", t->data.name, t->data.score);
		}
	}
}

///
/// メイン関数
///
int main() {
	int id;
	struct node *t = get_tree();
	scanf("%d ", &id);
	find_info(t, id);
	return 0;
}