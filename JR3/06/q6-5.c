/************************************************
 * マクロ部
 ************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/************************************************
 * 構造体等宣言部
 ************************************************/
typedef unsigned long  elementtype;    //リストの要素の型

typedef struct node {   //リストの要素
	elementtype element;
	struct node *next;
} node;

typedef struct node node;
typedef node* list;  //リストの要素のポインタをリストと定義

/************************************************
 * グローバル変数
 ************************************************/
int count = 0;	//追加した0の数

/************************************************
 * プロトタイプ宣言部
 ************************************************/
list init(void);
list cons(elementtype e, list l);
int length(list l);
void print_int_list_back(list l);
void carry(list l, int i);
list move(list l, int i);

/************************************************
 * 関数部
 ************************************************/
///
/// メイン関数
///
int main(int argc, char const *argv[]) {
	int len_1, len_2, len_ans;	//リストの長さ
	list l_1, l_2;	//入力リスト宣言
	//答え用リストのみ一つ要素をもたせておく
	//答えリストは一要素で数字一桁を表す
	list l_ans = (node*)malloc(sizeof(node));
	l_ans->element = 0;
	l_ans->next = NULL;
	//リストl_1, l_2への入力
	l_1 = init();
	l_2 = init();

	//長さの取得
	len_1 = length(l_1);
	len_2 = length(l_2);

	//掛け算の実行
	list l_1_move = l_1;
	list l_2_move = l_2;
	list l_ans_move = l_ans;
	for(int i = 0; i < len_2; i++) {
		l_ans_move = move(l_ans, i);
		l_1_move = l_1;
		for(int j = 0; j < len_1; j++) {
			l_ans_move->element += l_1_move->element * l_2_move->element;
			l_1_move = move(l_1_move, 1);
			l_ans_move = move(l_ans_move, 1);
		}
		l_2_move = move(l_2_move, 1);
	}

	len_ans = length(l_ans);	//長さの更新

	for(int i = 0; i < len_ans; i++) {	//繰り上がりの処理
		carry(l_ans, i);
	}

	//追加した0の分だけ0を削除する
	if(count >= 4) {
		count -= 4;
	}
	while(l_ans->element == 0 && l_ans->next != NULL) {
		l_ans = l_ans->next;
	}
	for(int i = 0; i < count; i++) {
		l_ans->element = l_ans->element / 10;
	}

	print_int_list_back(l_ans);

	return 0;
}

///
/// 標準入力から数を受け取り、それを4桁ずつに分け、分けたものをリストに格納した
/// リストを返す
///
list init(void) {
	list l = NULL;	//リストの作成
	int d = 0, i = 0;	//各種変数の宣言
	char c = 0;	//標準入力用
	//リストへ代入作業
	while((c = getchar()) != '\n') {
		if(i == 4) {
			l = cons(d, l);
			i = 0;
		}
		if(i == 0) {
			d = (int)c - '0';
			i++;
		} else {
			d = d * 10;
			d += (int)c - '0';
			i++;
		}
	}
	//余ったdの後ろに4桁の整数になるよう0を追加した後リストに追加
	for(; i < 4 && 0 < i; i++) {
		d = d * 10;
		count++;	//追加した0の数を覚えておく
	}
	if(i != 0) {
		l = cons(d, l);
		i = 0;
	}
	return l;	//リストを返す
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
	bool flag0 = true, flag_first = false;
	for(int i = len - 1; i > 0; i--) {
		list move = l;
		for(int j = 0; j < i; j++) {
			move = move->next;
		}
		if(move->element != 0) {
			flag0 = false;
		}
		if(flag0 == false && flag_first) {
			printf("%04ld", move->element);
		} else if(flag0 == false) {
			printf("%ld", move->element);
			flag_first = true;
		}
	}
	switch(count) {
		case 1:
			printf("%03ld", l->element);
			break;

		case 2:
			printf("%02ld", l->element);
			break;

		case 3:
			printf("%01ld", l->element);
			break;

		default:
			printf("%04ld", l->element);
			break;
	}
	printf("\n");
}

///
/// リストlのi番目の繰り上げの処理を行う
/// ただし、リストの最初の要素を0番目とする
///
void carry(list l, int i) {
	// リストをi+1番目まで作成する
	move(l, i + 1);
	// リストをi番目まで進める
	for(int j = 0; j < i; j++) {
		l = l->next;
	}

	//繰り上げ処理
	while (l->element >= 10000) {
		if(l->element >= 10000000) {
			l->next->element += 1000;
			l->element -= 10000000;
		} else if(l->element >= 1000000) {
			l->next->element += 100;
			l->element -= 1000000;
		} else if(l->element >= 100000) {
			l->next->element += 10;
			l->element -= 100000;
		} else if(l->element >= 10000) {
			l->next->element += 1;
			l->element -= 10000;
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