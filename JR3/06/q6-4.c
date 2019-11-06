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
void call(list l1, list l2, list l_ret, int i1, int i2, int i_ret);
void carry(list l, int i);
list move(list l, int i);

/************************************************
 * 関数部
/************************************************/
///
/// メイン関数
///
int main(int argc, char const *argv[]) {
	int d;
	int len_1, len_2, len_ans;   //リストの長さ
	char c;  //標準入力保存用
	list l_1 = NULL, l_2 = NULL;  //リスト宣言
	//答え用配列のみ一つ要素をもたせておく
	list l_ans = (node*)malloc(sizeof(node));
	l_ans->element = 0;
	l_ans->next = NULL;
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

	//掛け算の実行
	for(int i = 0; i < len_2; i++) {
		for(int j = 0; j < len_1; j++) {
			call(l_1, l_2, l_ans, j, i, i+j);
		}
	}

	len_ans = length(l_ans);    //長さの更新
	for(int i = 0; i < len_ans; i++) { //繰り上がりの処理
		carry(l_ans, i);
	}

	print_int_list_back(l_ans);

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
/// リストl_retのi_ret番目に、リストl1のi1番目の値とリストl2のi2番目の値の掛け合わせた値を加える
/// ただし、リストの最初の要素を0番目とする
///
void call(list l1, list l2, list l_ret, int i1, int i2, int i_ret) {
	// 各リストをそれぞれの場所まで進める
	l1 = move(l1, i1);
	l2 = move(l2, i2);
	l_ret = move(l_ret, i_ret);

	l_ret->element += l1->element * l2->element;
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
	while (l->element >= 10) {
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

///
/// リストlのi番目までリストを移動する
/// ただし、lのi番目が存在しなければ新たに要素を作成する
/// その際の値は0とする
///
list move(list l, int i) {
	for(int j = 0; j < i; j++) {
		if(l->next == NULL) {
			node *tmp = (node*)malloc(sizeof(node));    //新しく要素を作成
			//接続
			tmp->element = 0;
			tmp->next = NULL;
			l->next = tmp;
			l = l->next;
		} else {
			l = l->next;
		}
	}
	return l;
}
