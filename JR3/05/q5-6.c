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
typedef int elementtype;   //リストの要素の型

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
list cons_circ(elementtype e, list l);
void print_int_list_circ(list l);
list search_last(list l);
list max_place(list l);

/************************************************
 * 関数部
 ************************************************/
///
/// メイン関数
///
int main(int argc, char const *argv[]) {
    int i;
    char buf[128];  //標準入力保存用
    list l = NULL;  //リスト宣言
    //リストへの入力
    while(fgets(buf, sizeof(buf), stdin) != NULL) {
        sscanf(buf, "%d", &i);
        l = cons_circ(i, l);
    }
    //リストの内容表示
    print_int_list_circ(l);
    return 0;
}

///
/// 循環リストlにeを追加した循環リストを返す関数.
///
list cons_circ(elementtype e, list l) {
    node *tmp = (node*)malloc(sizeof(node));   //要素の確保
    tmp->element = e;

    if(l == NULL) { //循環リストが空だった場合
        tmp->next = tmp;
    } else {    //すでに要素がある場合
        tmp->next = l;
        l = search_last(l); //lの位置を最後尾に
        l->next = tmp;
    }
    return tmp->next;
}

///
/// 循環リストlに含まれる要素を先頭から順に[と]で挟んで標準出力に出力する関数.
/// 要素の型はint型であるものに限る.
///
void print_int_list_circ(list l) {
    l = max_place(l);   //最大値の位置を探索
    list tmp = l;   //最初の位置を記憶
    printf("[%d]", tmp->element);    //最初のみ例外的に出力
    while(l->next != tmp) {
        printf("[%d]", l->next->element);
        l = l->next;
    }
    printf("\n");
}

///
/// 循環リストの最後を見つけて返す
///
list search_last(list l) {
    list tmp = l;   //現在地を保存
    while (l->next != tmp) {
        l = l->next;
    }
    return l;
}

///
/// 循環リストの最大値の要素の位置を見つけて返す
///
list max_place(list l) {
    elementtype max_data = l->element;  //最大値
    list end_of_list = search_last(l);  //最後尾を記憶
    list ret_place = l; //返り値用変数
    l = l->next;
    while (l != end_of_list->next) {
        if(l->element >= max_data) {
            max_data = l->element;
            ret_place = l;
        }
        l = l->next;
    }
    return ret_place;
}
