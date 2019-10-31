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
        if(l->next == NULL) {   //一つ目はそのまま追加
            last->next = cons(i, NULL);
            last = last->next;
        } else {    //二つ目以降の場合
            list move = l;  //先頭からずらす用
            //順に比較
            int absi = abs(i);
            while (move->next != NULL) {
                int absmove = abs(move->next->element);
                if(i == move->next->element) {  //一致時追加しない
                    break;
                } else if(move->next->next != NULL && i == move->next->next->element) {
                    break;
                } else if(absi == absmove) {    //絶対値一致時
                    if(i < 0) { //iが負の場合
                        move->next->next = cons(i, move->next->next);
                        break;
                    } else {    //iが正の場合
                        move->next = cons(i, move->next);
                        break;
                    }
                } else if(absi > absmove) {  //初めて大きいと判断された場合その位置が適切
                    move->next = cons(i, move->next);
                    break;
                }
                move = move->next;
            }
            if(move->next == NULL) {    //最後尾に追加する必要があれば追加
                move->next = cons(i, NULL);
            }
        }
    }

    //リストの内容表示
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
        printf("%d\n", l->next->element);
        l = l->next;
    }
}
