/************************************************
 * マクロ部
/************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/************************************************
 * 構造体等宣言部
/************************************************/
typedef int elementtype;    //リストの要素の型

typedef struct node {   //リストの要素
	elementtype element;
	struct node *next;
} node;

typedef struct node* list;  //リストの要素のポインタをリストと定義

/************************************************
 * グローバル変数
/************************************************/

/************************************************
 * プロトタイプ宣言部
/************************************************/
list cons(elementtype e, list l);
int length(list l);
void print_int_list_back(list l);
void match(list l1, list l2, int i1, int i2);
void carry(list l, int i);

/************************************************
 * 関数部
/************************************************/
///
/// メイン関数
///
int main(int argc, char const *argv[]) {
	int d;
	int len_1, len_2;   //リストの長さ
	char c;  //標準入力保存用
	list l_1 = NULL, l_2 = NULL;  //リスト宣言
	//リストへの入力
	while((c = getchar()) != '\n') {
		d = (int)c - '0';
		l_1 = cons(d, l_1);
	}
	while((c = getchar()) != '\n') {
		d = (int)c - '0';
		l_2 = cons(d, l_2);
	}
	//長さの取得
	len_1 = length(l_1);
	len_2 = length(l_2);

	//足し算実行
	//桁数の少ない方を桁数の多い方へ足し合わせる
	if(len_1 > len_2) {
		for(int i = 0; i < len_2; i++) {
			match(l_1, l_2, i, i);
		}
		for(int i = 0; i < len_1; i++) { //繰り上がりの処理
			carry(l_1, i);
		}
		len_1 = length(l_1);    //長さの更新
		//表示
		print_int_list_back(l_1);
	} else {
		for(int i = 0; i < len_1; i++) {
			match(l_2, l_1, i, i);
		}
		for(int i = 0; i < len_2; i++) { //繰り上がりの処理
			carry(l_2, i);
		}
		len_2 = length(l_2);    //長さの更新
		//表示
		print_int_list_back(l_2);
	}

	return 0;
}

///
/// リストlの先頭にeを追加したリストを返す関数.
///
list cons(elementtype e, list l) {
	node *tmp = (node*)malloc(sizeof(node));
	tmp->element = e;
	tmp->next = l;
	return tmp;
}

///
/// リストlの長さ(要素の数)を返す関数.
///
int length(list l) {
	int i = 0;
	for (i = 0; l != NULL; i++) {
		l = l->next;
	}
	return i;
}

///
/// リストlに含まれる要素を後ろから標準出力に出力する関数.
/// 要素の型はint型であるものに限る.
///
void print_int_list_back(list l) {
	int len = length(l);
	for(int i = len - 1; i >= 0; i--) {
		list move = l;
		for(int j = 0; j < i; j++) {
			move = move->next;
		}
		printf("%d", move->element);
	}
	printf("\n");
}

///
/// リストl1のi1番目に、リストl2のi2番目の値を加える
/// ただし、リストの最初の要素を0番目とする
///
void match(list l1, list l2, int i1, int i2) {
	// 各リストをそれぞれの場所まで進める
	for(int i = 0; i < i1; i++) {
		l1 = l1->next;
	}
	for(int i = 0; i < i2; i++) {
		l2 = l2->next;
	}

	l1->element += l2->element;
}

///
/// リストlのi番目の繰り上げの処理を行う
/// ただし、リストの最初の要素を0番目とする
///
void carry(list l, int i) {
	// リストをi番目まで進める
	for(int j = 0; j < i; j++) {
		l = l->next;
	}

	//繰り上げ処理
	if(l->element >= 10) {
		l->element -= 10;
		if(l->next == NULL) {   //i番目がlの最後の要素の場合
			node *tmp = (node*)malloc(sizeof(node));    //新しく要素を作成
			//接続
			tmp->element = 1;
			tmp->next = NULL;
			l->next = tmp;
		} else {
			l->next->element += 1;
		}
	}
}
