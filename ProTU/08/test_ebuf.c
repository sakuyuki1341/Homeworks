#include <stdio.h>
#include <string.h>
#include "ebuf.h"


void expect_str(char *s1, char *s2, char *msg) {
  printf("%s '%s':'%s' %s\n", strcmp(s1, s2)?"NG":"OK", s1, s2, msg);
}

int main(void) {
  ebufp e = ebuf_new();
  ebuf_insert(e, "abc"); ebuf_insert(e, "def");
  ebuf_top(e); expect_str(ebuf_str(e), "abc", "line 1: abc");
  ebuf_forward(e); expect_str(ebuf_str(e), "def", "line 2: def");
  ebuf_insert(e, "ghi"); ebuf_top(e);
  ebuf_forward(e); expect_str(ebuf_str(e), "ghi", "new line 2: ghi");
  ebuf_forward(e); expect_str(ebuf_str(e), "def", "new line 3: def");
  return 0;
}
