#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#define ENSHU1_EX
//#define ENSHU1_A
//#define ENSHU1_B
#define ENSHU1_C
//#define ENSHU1_D

struct node {
    double data;
    struct node *next;
};
typedef struct node *nodep;

nodep node_new(double d, nodep n) {
    nodep p = (nodep)malloc(sizeof(struct node));
    p->data = d; p->next = n;
    return p;
}

void plist(nodep p) {
    while(p != NULL) {
        printf(" %g", p->data);
        p = p->next;
    }
    printf("\n");
}

nodep mklist(int n, char *a[]) {
    nodep p = NULL;
    for(int i = n-1; i >= 0; --i) {
        p = node_new(atof(a[i]), p);
    }
    return p;
}

int main(int argc, char *argv[]) {
    nodep p = mklist(argc-1, argv+1); plist(p);
#ifdef ENSHU1_EX
    p->next->next = p->next->next->next; plist(p);
    p->next->next = node_new(1.0, p->next->next); plist(p);
#endif
#ifdef ENSHU1_A
    nodep a = p;    // aはリストの先頭
    // aをリストの最後から一つ前に
    while(a->next->next != NULL) {
        a = a->next;
    }

    a->next->next = p;  // リストの最後を先頭に接続
    p = a->next;    // リストの先頭を更新
    a->next = NULL;     // リストの循環を切断

    // リストを先頭から表示
    plist(p);
#endif
#ifdef ENSHU1_B
    nodep a = p; // aをリストの先頭に
    // aをリストの最後に
    while(a->next != NULL) {
        a = a->next;
    }

    a->next = p;    // リストの最後の次を先頭に
    p = p->next;    // リストの先頭の更新
    a->next->next = NULL;   // リストの最後の更新

    // リストを先頭から表示
    plist(p);
#endif
#ifdef ENSHU1_C
    // リストの2～4番目のアドレスを保存
    nodep a_2 = p->next;
    nodep a_3 = p->next->next;
    nodep a_4 = p->next->next->next;

    // リストの順番を入れ替える
    p->next = a_3;
    p->next->next = a_2;
    p->next->next->next = a_4;

    // リストを先頭から表示
    plist(p);
#endif
#ifdef ENSHU1_D
    // 先頭のアドレスを保存
    nodep a = p;

    // すべての要素において実行
    while(p != NULL) {
        nodep cp = node_new(p->data, p->next);
        p->next = cp;
        p = p->next->next;  // pを次の要素へ移す
    }


    // リストを先頭から表示
    plist(a);
#endif
    return 0;
}
