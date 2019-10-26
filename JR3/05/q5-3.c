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
typedef char elementtype;   //リストの要素の型

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
void print_char_list(list l);
void insert(list l, elementtype e);

/************************************************
 * 関数部
 ************************************************/
///
/// メイン関数
///
int main(int argc, char const *argv[]) {
    int i;
    char c, buf[128];   //標準入力保存用
    list l, last;   // 頭付きリスト宣言
    //頭付きリスト初期化
    l = list_init();
    last = l;

    fgets(buf, sizeof(buf), stdin); //1行分標準入力から読み取り
    //リストへ読み取りした文を入れる
    for(i = 0; (c = buf[i]) != '\n'; ++i) {
        last->next = cons(c, NULL);
        last = last->next;
    }
    print_char_list(l); //リストを表示

    //標準入力から挿入指示を受け取り実行
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        sscanf(buf, "%d %c", &i, &c);

        //挿入位置を設定
        list tmp = l;
        for(int j = 0; j < i && tmp->next != NULL; j++) {
            tmp = tmp->next;
        }

        insert(tmp, c); //リストへ挿入
        print_char_list(l); //リストを表示
    }
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
    node *tmp = (node*)malloc(sizeof(node));   //要素の確保
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

///
/// リストlに含まれる要素を先頭から順に標準出力に出力する関数.
/// 要素の型はchar型であるものに限る.
///
void print_char_list(list l) {
    for(int i = 0; l->next != NULL; i++) {
        printf("%c", l->next->element);
        l = l->next;
    }
    printf("\n");
}

///
/// 「頭のある」連結リストに対し、先頭に節点を挿入する関数
///
void insert(list l, elementtype e) {
    node *tmp = (node*)malloc(sizeof(node));
    tmp->element = e;
    tmp->next = l->next;
    l->next = tmp;
}
