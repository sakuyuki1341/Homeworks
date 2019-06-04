#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#define ENSHU2_EX
//#define ENSHU2_A
//#define ENSHU2_B
//#define ENSHU2_C
//#define ENSHU2_D
//#define ENSHU2_E

struct node { double data; struct node *next; };
typedef struct node *nodep;

nodep node_new(double d, nodep n) {
    nodep p = (nodep)malloc(sizeof(struct node));
    p->data = d; p->next = n; return p;
}

nodep mklist(int n, char *a[]) {
    if(n == 0) { return NULL; }
    return node_new(atof(*a), mklist(n-1, a+1));
}

/*==================================================================*
 * 関数plist: リストpのデータを順に表示
 *==================================================================*/
void plist(nodep p) {
    if(p == NULL) { printf("\n"); return; }
    printf(" %g", p->data); plist(p->next);
}

/*==================================================================*
 * 関数nconc: リストpの後ろにqをくっつける
 *==================================================================*/
void nconc(nodep p, nodep q) {
    while(p != NULL && p->next != NULL) { p = p->next; }
    if(p != NULL) { p->next = q; }
}

/*==================================================================*
 * 関数delnode: リストpのn番目を削除する
 *==================================================================*/
void delnode(nodep p, int n) {
    while(--n > 0 && p != NULL) { p = p->next; }
    if(p != NULL && p->next != NULL) { p->next = p->next->next; }
}

/*==================================================================*
 * 関数addlist: リストx, yの要素をそれぞれ足し合わせる
 *==================================================================*/
nodep addlist(nodep x, nodep y) {
    if(x == NULL) { return y; }
    if(y == NULL) { return x; }
    return node_new(x->data+y->data, addlist(x->next, y->next));
}

/*==================================================================*
 * 関数timeslist: リストx, yの要素をそれぞれ掛け合わせる
 *==================================================================*/
nodep timeslist(nodep x, nodep y) {
    if(x == NULL) { return y; }
    if(y == NULL) { return x; }
    return node_new(x->data*y->data, timeslist(x->next, y->next));
}

/*==================================================================*
 * 関数getl: 文字配列sに1行分の文字列を入れ込んでいく
 *==================================================================*/
bool getl(char s[], int lim) {
    int c, i = 0;
    for(c = getchar(); c != EOF && c != '\n'; c = getchar()) {
        s[i++] = c; if(i+1 >= lim) { break; }
    }
    s[i] = '\0'; return c != EOF;
}

/*==================================================================*
 * 関数parse: 与えられた文字列sを空白で分け、それぞれ別の文字列とする
 * また、分けられた文字列は文字列配列aに入れ込まれる。
 * 返り値は、分けられた文字列の個数となる。
 *==================================================================*/
int parse(char *a[], char *s) {
    int i, k = 0, len = strlen(s);
    for(i = 0; i < len; ++i) {
        if(s[i] == ' ') { s[i] = '\0'; }
        if(s[i] != '\0' && (i == 0 || s[i-1] == '\0')) { a[k++] = s+i; }
    }
    return k;
}


int main(int argc, char *argv[]) {
    char buf[200], *cmd[20];
    nodep list = NULL;
    while(true) {
        printf("> "); if(!getl(buf, 200)) { break; }
        int k = parse(cmd, buf);
        if(k > 0 && strcmp(cmd[0], "q") == 0) {
            break;
        } else if(k > 0 && strcmp(cmd[0], "e") == 0) { // enter list
            list = mklist(k-1, cmd+1);
        } else if(k > 0 && strcmp(cmd[0], "a") == 0) { // append list
            nconc(list, mklist(k-1, cmd+1));
        } else if(k > 1 && strcmp(cmd[0], "add") == 0) { // add list
            list = addlist(list, mklist(k-1, cmd+1));
        } else if(k > 1 && strcmp(cmd[0], "times") == 0) { // times list
            list = timeslist(list, mklist(k-1, cmd+1));
        } else if(k > 1 && strcmp(cmd[0], "d") == 0) { // delete item
            delnode(list, atoi(cmd[1]));
        } else {
            plist(list);
        }
    }
    return 0;
}
