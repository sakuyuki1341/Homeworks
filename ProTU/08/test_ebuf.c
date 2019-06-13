#include <stdio.h>
#include <string.h>
#include "ebuf.h"

//#define ENSHU1_EX
//#define ENSHU1_A
//#define ENSHU1_B
#define ENSHU1_C

void expect_str(char *s1, char *s2, char *msg) {
    printf("%s '%s':'%s' %s\n", strcmp(s1, s2)?"NG":"OK", s1, s2, msg);
}

int main(void) {
#ifdef ENSHU1_EX
    ebufp e = ebuf_new();
    ebuf_insert(e, "abc"); ebuf_insert(e, "def");
    ebuf_top(e); expect_str(ebuf_str(e), "abc", "line 1: abc");
    ebuf_forward(e); expect_str(ebuf_str(e), "def", "line 2: def");
    ebuf_insert(e, "ghi"); ebuf_top(e);
    ebuf_forward(e); expect_str(ebuf_str(e), "ghi", "new line 2: ghi");
    ebuf_forward(e); expect_str(ebuf_str(e), "def", "new line 3: def");
#endif

#ifdef ENSHU1_A
    ebufp e = ebuf_new();
    ebuf_insert(e, "abc");
    ebuf_insert(e, "def");
    ebuf_top(e);

    ebuf_replace(e, "jkl");   // ここでabcをjklに変更
    expect_str(ebuf_str(e), "jkl", "line 1: jkl");

    ebuf_forward(e);
    expect_str(ebuf_str(e), "def", "line 2: def");
#endif

#ifdef ENSHU1_B
    ebufp e = ebuf_new();
    ebuf_insert(e, "abc");
    ebuf_insert(e, "def");
    ebuf_top(e);

    ebuf_delete(e);   // ここでabcを削除
    expect_str(ebuf_str(e), "def", "line 1: def");

    ebuf_forward(e);  // ここでcurがEOFを指すように
    ebuf_delete(e);   // ここでEOFを削除するように試みる
#endif

#ifdef ENSHU1_C
    ebufp e = ebuf_new();
    ebufp y = ebuf_new(); // ヤンク用リスト
    ebuf_insert(e, "abc");
    ebuf_insert(e, "def");
    ebuf_top(e);

    ebuf_delete_y(e, y);   // ここでabcを削除
    expect_str(ebuf_str(e), "def", "line 1: def");

    ebuf_insert(e, "jkl");
    ebuf_top(e);
    expect_str(ebuf_str(e), "jkl", "line 1: jkl");
    ebuf_forward(e);

    ebuf_yank(e, y);    // ここでabcを戻す
    expect_str(ebuf_str(e), "abc", "line 2: abc");
#endif
    return 0;
}
