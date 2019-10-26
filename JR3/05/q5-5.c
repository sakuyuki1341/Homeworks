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
void delete(list l);
int search(list l, elementtype e);
list move(list l, int num);

/************************************************
 * 関数部
 ************************************************/
///
/// メイン関数
///
int main(int argc, char const *argv[]) {
    int place[4];   //括弧の場所保存用
    char c, buf[128];   //標準入力保存用
    /*
    *[0]:標準入力そのまま
    *[1]:()で囲まれたもの
    *[2]:[]で囲まれたもの
    *[3]:出力するためののも
    */
    list l[4], last[4];   // 頭付きリスト宣言
    //頭付きリスト初期化
    for(int i = 0; i < 4; i++) {
        l[i] = list_init();
        last[i] = l[i];
    }

    fgets(buf, sizeof(buf), stdin); //1行分標準入力から読み取り
    //リストへ読み取りした文を入れる
    for(int i = 0; (c = buf[i]) != '\n'; ++i) {
        last[0]->next = cons(c, NULL);
        last[0] = last[0]->next;
    }

    //括弧がなくなるまで探索
    while (true) {
        place[0] = search(l[0], '[');
        place[1] = search(l[0], '(');
        place[2] = search(l[0], ')');
        place[3] = search(l[0], ']');
        if(place[0] == 0 && place[1] == 0 && place[2] == 0 && place[3] == 0) {
            break;
        }
        //[]と()と[()]と[]()と([])と()[]の6パターンに分類
        if(place[1] == 0) { //[]
            //[]内にある文字を別リストに記録する
            for(int i = place[0] + 1; i < place[3]; i++) {
                list tmp = move(l[0], i);
                last[2]->next = cons(tmp->next->element, NULL);
                last[2] = last[2]->next;
            }

            //[]も含めその中の文字を元リストから削除する
            list tmp = move(l[0], place[0]);
            for(int i = place[0]; i <= place[3]; i++) {
                delete(tmp);
            }
        } else if(place[0] == 0) {  //()
            //()内にある文字を別リストに記録する
            for(int i = place[1] + 1; i < place[2]; i++) {
                list tmp = move(l[0], i);
                last[1]->next = cons(tmp->next->element, NULL);
                last[1] = last[1]->next;
            }

            //()も含めその中の文字を元リストから削除する
            list tmp = move(l[0], place[1]);
            for(int i = place[1]; i <= place[2]; i++) {
                delete(tmp);
            }
        } else if(place[0] < place[1] && place[1] < place[3]) { //[()]
            //()内にある文字を別リストに記録する
            for(int i = place[1] + 1; i < place[2]; i++) {
                list tmp = move(l[0], i);
                last[1]->next = cons(tmp->next->element, NULL);
                last[1] = last[1]->next;
            }

            //()も含めその中の文字を元リストから削除する
            list tmp = move(l[0], place[1]);
            for(int i = place[1]; i <= place[2]; i++) {
                delete(tmp);
            }
        } else if(place[0] < place[1] && place[3] < place[1]) { //[]()
            //[]内にある文字を別リストに記録する
            for(int i = place[0] + 1; i < place[3]; i++) {
                list tmp = move(l[0], i);
                last[2]->next = cons(tmp->next->element, NULL);
                last[2] = last[2]->next;
            }

            //[]も含めその中の文字を元リストから削除する
            list tmp = move(l[0], place[0]);
            for(int i = place[0]; i <= place[3]; i++) {
                delete(tmp);
            }
        } else if(place[1] < place[0] && place[0] < place[2]) { //([])
            //[]内にある文字を別リストに記録する
            for(int i = place[0] + 1; i < place[3]; i++) {
                list tmp = move(l[0], i);
                last[2]->next = cons(tmp->next->element, NULL);
                last[2] = last[2]->next;
            }

            //[]も含めその中の文字を元リストから削除する
            list tmp = move(l[0], place[0]);
            for(int i = place[0]; i <= place[3]; i++) {
                delete(tmp);
            }
        } else if(place[1] < place[0] && place[2] < place[0]) { //()[]
            //()内にある文字を別リストに記録する
            for(int i = place[1] + 1; i < place[2]; i++) {
                list tmp = move(l[0], i);
                last[1]->next = cons(tmp->next->element, NULL);
                last[1] = last[1]->next;
            }

            //()も含めその中の文字を元リストから削除する
            list tmp = move(l[0], place[1]);
            for(int i = place[1]; i <= place[2]; i++) {
                delete(tmp);
            }
        }
    }

    print_char_list(l[1]);
    print_char_list(l[0]);
    print_char_list(l[2]);
    printf("\n");

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
    //printf("\n");
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

///
/// 「頭のある」連結リストに対し、先頭の接点を削除する関数
///
void delete(list l) {
    list tmp = l->next; //要素を開放するため確保
    l->next = l->next->next;    //要素を一つ飛ばす
    free(tmp);  //開放
}

///
/// 連結リストに対し、指定された要素を先頭から探索し、リストの先頭を0として位置を返す
///
int search(list l, elementtype e) {
    int i = 0;
    //探索
    l = l->next;
    for(i = 1; l->next != NULL && l->element != e; i++) {
        l = l->next;
    }
    //要素を見つけた場合、位置を返す
    if(l->element == e) {
        return i;
    }
    return 0;   //未発見時先頭を返す
}

///
/// 指定された位置の手前までリストを進める
///
list move(list l, int num) {
    list tmp = l;
    for(int i = 0; i < num - 1; i++) {
        tmp = tmp->next;
    }
    return tmp;
}
