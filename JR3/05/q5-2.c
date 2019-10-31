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

typedef struct node {   //リストの要素
    elementtype element;
    struct node *next;
} node;

typedef struct node* list;  //リストの要素のポインタをリストと定義

/************************************************
 * グローバル変数
 ************************************************/

/************************************************
 * プロトタイプ宣言部
 ************************************************/
list list_init(void);
list cons(elementtype e, list l);
int length(list l);
void print_int_list(list l);

/************************************************
 * 関数部
 ************************************************/
///
/// メイン関数
///
int main(int argc, char const *argv[]) {
    int i;
    char buf[128];  //標準入力保存用
    list l, last;  //頭付きリスト宣言
    //頭付きリストの初期化
    l = list_init();
    last = l;
    //リストへの入力
    while(fgets(buf, sizeof(buf), stdin) != NULL) {
        sscanf(buf, "%d", &i);
        last->next = cons(i, NULL);
        last = last->next;
    }
    //リストの内容表示
    printf("length=%d\n", length(l));
    print_int_list(l);
    return 0;
}

///
/// 頭付きリストの初期化
///
list list_init(void) {
    node *tmp = (node*)malloc(sizeof(node));
    tmp->next = NULL;
    return tmp;
}

///
/// リストlの先頭にeを追加したリストを返す関数.
///
list cons(elementtype e, list l) {
    struct node *tmp = (struct node*)malloc(sizeof(struct node));
    tmp->element = e;
    tmp->next = l;
    return tmp;
}

///
/// リストlの長さ(要素の数)を返す関数.
///
int length(list l) {
    int i = 0;
    for (i = 0; l->next != NULL; i++) {
        l = l->next;
    }
    return i;
}

///
/// リストlに含まれる要素を先頭から順に[と]で挟んで標準出力に出力する関数.
/// 要素の型はint型であるものに限る.
///
void print_int_list(list l) {
    for(int i = 0; l->next != NULL; i++) {
        printf("[%d]", l->next->element);
        l = l->next;
    }
    printf("\n");
}
