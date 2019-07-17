// treedemo.c --- demonstration of bstree operation
#include <stdlib.h>
#include <stdio.h>
#include "itbl.h"

int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  itblp p = itbl_new();
  for(int i = 1; i < argc; ++i) {
    int v = atoi(argv[i]);
    if(v >= 0) { itbl_put(p, v, i); }
//  else       { itbl_delete(p, -v); }
    itbl_pr(p);
  }
  return 0;
}
