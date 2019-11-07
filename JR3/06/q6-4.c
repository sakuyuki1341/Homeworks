/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

/************************************************
 * 構造体等宣言部
 ************************************************/
typedef int elementtype;    //リストの要素の型

typedef struct node {   //リストの要素
	elementtype element;
	struct node *next;
} node;

typedef struct node node;
typedef node* list;  //リストの要素のポインタをリストと定義

/************************************************
 * グローバル変数
 ************************************************/

/************************************************
 * プロトタイプ宣言部
 ************************************************/
list cons(elementtype e, list l);
int length(list l);
void print_int_list_back(list l);
void call(list l1, list l2, list l_ret, int i1, int i2, int i_ret);
void carry(list l, int i);
list move(list l, int i);

/************************************************
 * 関数部
 ************************************************/
///
/// メイン関数(
///
int main(int argc, char const *argv[]) {
	clock_t start, end;
	start = clock();
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
	list l_1_move = l_1;
	list l_2_move = l_2;
	list l_ans_move = l_ans;
	for(int i = 0; i < len_2; i++) {
		for(int j = 0; j < len_1; j++) {
			l_ans_move->element += l_1_move->element * l_2_move->element;
			l_1_move = move(l_1_move, 1);
			l_ans_move = move(l_ans_move, 1);
		}
		l_1_move = l_1;
		l_2_move = move(l_2_move, 1);
		l_ans_move = move(l_ans, i);
	}

	len_ans = length(l_ans);    //長さの更新
	for(int i = 0; i < len_ans; i++) { //繰り上がりの処理
		carry(l_ans, i);
	}

	print_int_list_back(l_ans);
	end = clock();
//	printf("operating times:%d[ms]\n", end - start);

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
	int flag0 = true;
	for(int i = len - 1; i >= 0; i--) {
		list move = l;
		for(int j = 0; j < i; j++) {
			move = move->next;
		}
		if(move->element != 0) {
			flag0 = false;
		}
		if(flag0 == false) {
			printf("%d", move->element);
		}
	}
	if(flag0 == true) {
		printf("0");
	}
	printf("\n");
}

///
/// リストlのi番目の繰り上げの処理を行う
/// ただし、リストの最初の要素を0番目とする
///
void carry(list l, int i) {
	// リストをi+4番目まで作成する
	move(l, i + 5);
	// リストをi番目まで進める
	for(int j = 0; j < i; j++) {
		l = l->next;
	}

	//繰り上げ処理
	while (l->element >= 10) {
		if(l->element >= 100000) {
			l->next->next->next->next->next->element += 1;
			l->element -= 100000;
		} else if(l->element >= 10000) {
			l->next->next->next->next->element += 1;
			l->element -= 10000;
		} else if(l->element >= 1000) {
			l->next->next->next->element += 1;
			l->element -= 1000;
		} else if(l->element >= 100) {
			l->next->next->element += 1;
			l->element -= 100;
		} else if(l->element >= 10) {
			l->next->element += 1;
			l->element -= 10;
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
