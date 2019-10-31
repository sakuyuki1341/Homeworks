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
typedef int elementtype;    //リストの要素の型

typedef struct dlnode {   //リストの要素
    elementtype element;
    struct dlnode *next, *prev;
} dlnode;

typedef struct dlnode* list;  //リストの要素のポインタをリストと定義

/************************************************
 * グローバル変数
 ************************************************/

/************************************************
 * プロトタイプ宣言部
 ************************************************/
void insert(dlnode *p, elementtype e);
void delete(dlnode *p);
void print_dllist(dlnode *d);
void append_dllist(dlnode *d1, dlnode *d2);

/************************************************
 * 関数部
 ************************************************/
///
/// メイン関数
///
int main(int argc, char const *argv[]) {
    char buf[128];
    int i;
    dlnode *d1, *d2;
    //双方向リストの初期化
    d1 = (dlnode*)malloc(sizeof(dlnode));
    d2 = (dlnode*)malloc(sizeof(dlnode));
    d1->prev = d1; d1->next = d1;
    d2->prev = d2; d2->next = d2;

    while(fgets(buf, sizeof(buf), stdin) != NULL) {
        sscanf(buf, "%d", &i);
        insert(d1, i);  //d1の末尾にiを挿入
        insert(d2, i);  //d2の末尾にiを挿入
    }
    print_dllist(d1);   //d1の内容を出力
    print_dllist(d2);   //d2の内容を出力
    //d1の奇数要素を削除
    dlnode *move1 = d1;
    move1 = move1->next;
    while (move1 != d1) {
        if(abs(move1->element) % 2 == 1) {
            delete(move1);
        }
        move1 = move1->next;
    }
    //d2の偶数要素を削除
    dlnode *move2 = d2;
    move2 = move2->next;
    while (move2 != d2) {
        if(abs(move2->element) % 2 == 0) {
            delete(move2);
        }
        move2 = move2->next;
    }

    print_dllist(d1);   //d1の内容を出力
    print_dllist(d2);   //d2の内容を出力

    append_dllist(d1, d2);   //d1,d2を連結
    print_dllist(d1);   //連結されたリストを出力
    return 0;
}

///
/// pの指している節点のprevに,elementとしてeを含む節点を挿入する
///
void insert(dlnode *p, elementtype e) {
    dlnode *tmp = (dlnode*)malloc(sizeof(dlnode));  //新たな節点宣言
    tmp->element = e;
    //節点の更新
    tmp->next = p;
    tmp->prev = p->prev;
    p->prev->next = tmp;
    p->prev = tmp;
}

///
/// pの指している節点のみを削除する関数
///
void delete(dlnode *p) {
    //節点の更新
    p->next->prev = p->prev;
    p->prev->next = p->next;
    free(p);
}

///
/// dの指しているダミーの節点からnextの順に全節点のelementを[]で挟んで出力
/// その後、prevの順に全節点のelementを{}で挟んで出力
///
void print_dllist(dlnode *d) {
    dlnode *move = d;    //動かすポインタを確保
    //nextの順に出力
    move = move->next;  //ひとつだけ先にずらす
    while(move != d) {
        printf("[%d]", move->element);
        move = move->next;
    }

    //prevの順に出力
    move = move->prev;  //ひとつだけ先にずらす
    while (move != d) {
        printf("{%d}", move->element);
        move = move->prev;
    }
    printf("\n");
}

///
/// d1,d2の指している節点をダミーの節点とする2つの双方向リストを連結する
///
void append_dllist(dlnode *d1, dlnode *d2) {
    //連結の更新
    d1->prev->next = d2->next;
    d2->next->prev = d1->prev;
    d1->prev = d2->prev;
    d2->prev->next = d1;
    free(d2);   //メモリ解放
}
