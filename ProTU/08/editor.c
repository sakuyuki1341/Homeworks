// 演習2_a ---> 完了
// 演習2_b ---> 完了
// 演習2_c ---> 完了
// 演習2_d ---> 完了
// 演習2_e ---> 完了



#include <stdio.h>
#include <string.h>
#include "ebuf.h"


bool getl(char s[], int lim) {
  int c, i = 0;
  for(c = getchar(); c != EOF && c != '\n'; c = getchar()) {
    s[i++] = c; if(i+1 >= lim) { break; }
  }
  s[i] = '\0'; return c != EOF;
}

bool readfile(ebufp e, char *fname) {
  char str[200];
  FILE *f = fopen(fname, "r");
  if(f == NULL) { return false; }
  while(fgets(str, 200, f) != NULL) {
    int len = strlen(str);
    if(len > 0) { str[len-1] = '\0'; }
    ebuf_insert(e, str);
  }
  fclose(f); return true;
}

bool writefile(ebufp e, char *fname) {
  FILE *f = fopen(fname, "w");
  if(f == NULL) { return false; }
  ebuf_top(e);
  while(!ebuf_iseof(e)) {
    fprintf(f, "%s\n", ebuf_str(e)); ebuf_forward(e);
  }
  fclose(f); return true;
}

int main(void) {
  char buf[200];
  ebufp e = ebuf_new();
  ebufp y = ebuf_new();
  printf("> ");
  while(getl(buf, 200)) {
    if(buf[0] == 'q') { // quit
      break;

    } else if(buf[0] == 'p') { // print
      printf("   %s\n", ebuf_str(e));

    } else if(buf[0] == 't') { // top
      ebuf_top(e);

    } else if(buf[0] == 'f') { // fwd
      if(buf[1] >= 1) {
        for(int i = 0; i < buf[1]; i++) {
          ebuf_forward(e);
        }
      } else {
        ebuf_forward(e);
      }

    } else if(buf[0] == 'b') { // back
      if(buf[1] >= 1) {
        for(int i = 0; i < buf[1]; i++) {
          ebuf_backward(e);
        }
      } else {
        ebuf_backward(e);
      }

    } else if(buf[0] == 'i') { // insert
      ebuf_insert(e, buf+1);

    } else if(buf[0] == 'r') { // read file
      readfile(e, buf+1);

    } else if(buf[0] == 'w') { // write file
      writefile(e, buf+1);

    } else if(buf[0] == 'd') { // delete
      ebuf_delete_y(e, y);

    } else if(buf[0] == 'y') {
      ebuf_yank(e, y);

    } else if(buf[0] == 'r') { // replace
      ebuf_replace(e, buf+1);

    } else {  // other --- fwd and print
      ebuf_forward(e); printf("   %s\n", ebuf_str(e));
    }
    printf("> ");
  }
  return 0;
}
