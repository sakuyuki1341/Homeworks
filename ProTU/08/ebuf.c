#include <stdlib.h>
#include <string.h>
#include "ebuf.h"


struct line {
    struct line *prev, *next; char str[MAXSTR];
};

struct ebuf { struct line *head, *cur; };

/*========================================================*
 * 関数ebuf_new: 新規バッファの作成
 *========================================================*/
ebufp ebuf_new() {
    ebufp r = (ebufp)malloc(sizeof(struct ebuf));
    r->head = (struct line*)malloc(sizeof(struct line));
    r->cur = r->head->next = r->head->prev = r->head;
    strcpy(r->head->str, "EOF"); return r;
}

/*========================================================*
 * 関数ebuf_iseof: 現在行がEOF行かどうか調べる。
 * 戻り値はEOFならtrue, EOFでないならfalse
 *========================================================*/
bool ebuf_iseof(ebufp e) { return e->cur == e->head; }

/*========================================================*
 * 関数ebuf_forward: 現在行を一行先に移動
 *========================================================*/
bool ebuf_forward(ebufp e) {
    if(e->cur == e->head) { return false; }
    e->cur = e->cur->next; return true;
}

/*========================================================*
 * 関数ebuf_backward: 現在行を一行前に移動
 *========================================================*/
bool ebuf_backward(ebufp e) {
    if(e->cur->prev == e->head) { return false; }
    e->cur = e->cur->prev; return true;
}

/*========================================================*
 * 関数ebuf_top: 現在行を先頭に移動
 *========================================================*/
void ebuf_top(ebufp e) { e->cur = e->head->next; }

/*========================================================*
 * 関数ebuf_str: 現在行の文字列を返す
 *========================================================*/
char *ebuf_str(ebufp e) { return e->cur->str; }

/*========================================================*
 * 関数ebuf_insert: 現在行の上に指定した文字列を持つ行を插入
 *========================================================*/
void ebuf_insert(ebufp e, char *s) {
    struct line *p = (struct line*)malloc(sizeof(struct line));
    strncpy(p->str, s, MAXSTR); p->str[MAXSTR-1] = '\0';
    p->prev = e->cur->prev; p->next = e->cur;
    e->cur->prev->next = p; e->cur->prev = p;
}

/*========================================================*
 * 関数ebuf_replace: 現在行の内容を指定した文字列に
 * 取り換える。
 *========================================================*/
void ebuf_replace(ebufp e, char *s) {
    strcpy(e->cur->str, s);
}

/*========================================================*
 * 関数ebuf_delete: 現在行を削除する。削除した後の
 * 現在行は一つ先を指す。
 *========================================================*/
void ebuf_delete(ebufp e) {
    if(!ebuf_forward(e)) {
        printf("EOF行は削除できない\n");
    } else {
        e->cur->prev->prev->next = e->cur;
        e->cur->prev = e->cur->prev->prev;
    }
}

/*========================================================*
 * 関数ebuf_delete_y: 現在行を削除し、削除されたセルが
 * ヤンク用のリストに追加される。
 * 削除した後の現在行は一つ先を指す。
 *========================================================*/
void ebuf_delete_y(ebufp e, ebufp y) {
    if(ebuf_iseof(e)) {
        printf("EOF行は削除できない\n");
    } else {
        // 接続の順番変更(第一段階)
        e->cur->prev->next = e->cur->next;
        e->cur->next = y->cur;
        y->cur->prev->next = e->cur;

        // eの現在行を一つ先に移す
        e->cur = e->cur->prev->next;

        // 接続の順番変更(第二段階)
        e->cur->prev = e->cur->prev->prev;
        y->cur->prev->next->prev = y->cur->prev;
        y->cur->prev = y->cur->prev->next;
    }
}

/*========================================================*
 * 関数ebuf_yank: 削除された行を、現在行の上に插入する。
 *========================================================*/
void ebuf_yank(ebufp e, ebufp y) {
    // 接続の順番変更(第一段階)
    y->cur->prev->prev->next = y->cur;
    y->cur->prev->next = e->cur;
    e->cur->prev->next = y->cur->prev;
    y->cur->prev = y->cur->prev->prev;
    e->cur->prev->next->prev = e->cur->prev;
    e->cur->prev = e->cur->prev->next;

    // eの現在行を前に移す
    ebuf_backward(e);
}
