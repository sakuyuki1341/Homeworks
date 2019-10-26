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
typedef int elementtype;

typedef struct node {
    elementtype element;
    node * next;
} node;

typedef node* list;

/************************************************
 * グローバル変数
 ************************************************/

/************************************************
 * プロトタイプ宣言部
 ************************************************/
list cons(elementtype e, list l);
int length(list l);
void print_int_list(list l);

/************************************************
 * 関数部
 ************************************************/
int main(int argc, char const *argv[]) {
    int i;
    char buf[128];
    list l = NULL;
    while(fgets(buf, sizeof(buf), stdin) != NULL) {
        sscanf(buf, "%d", &i);
        l = cons(i, l);
    }
    printf("length=%d\n", length(l));
    print_int_list(l);
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
    for
}

///
/// リストlに含まれる要素を先頭から順に[と]で挟んで標準出力に出力する関数.
/// 要素の型はint型であるものに限る.
///
void print_int_list(list l) {

}
