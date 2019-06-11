#include <stdio.h>
#include "ebuf.h"

int main(void) {
  ebufp e = ebuf_new();
  ebuf_insert(e, "abc");
  ebuf_insert(e, "def");
  ebuf_insert(e, "ghi");
  ebuf_top(e);
  while(!ebuf_iseof(e)) {
    printf("%s\n", ebuf_str(e)); ebuf_forward(e);
  }
  while(ebuf_backward(e)) { printf("%s\n", ebuf_str(e)); }
  return 0;
}
