#include <stdio.h>
#include "ebuf.h"


bool getl(char s[], int lim) {
  int c, i = 0;
  for(c = getchar(); c != EOF && c != '\n'; c = getchar()) {
    s[i++] = c; if(i+1 >= lim) { break; }
  }
  s[i] = '\0'; return c != EOF;
}

int main(void) {
  char buf[200];
  ebufp e = ebuf_new();
  printf("> ");
  while(getl(buf, 200)) {
    if(buf[0] == 'q') { // quit
      break;
    } else if(buf[0] == 'p') { // print
      printf("   %s\n", ebuf_str(e));
    } else if(buf[0] == 't') { // top
      ebuf_top(e); 
    } else if(buf[0] == 'f') { // fwd
      ebuf_forward(e); 
    } else if(buf[0] == 'b') { // back
      ebuf_backward(e); 
    } else if(buf[0] == 'i') { // insert
      ebuf_insert(e, buf+1);
    } else {  // other --- fwd and print
      ebuf_forward(e); printf("   %s\n", ebuf_str(e));
    }
    printf("> ");
  }
  return 0;
}
