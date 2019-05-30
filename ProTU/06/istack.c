#include <stdlib.h>
#include "istack.h"
struct istack { int ptr; int *arr; };
istackp istack_new(int size) {
  istackp p = (istackp)malloc(sizeof(struct istack));
  p->ptr = 0; p->arr = (int*)malloc(size * sizeof(int));
  return p;
}
bool istack_isempty(istackp p) { return p->ptr <= 0; }
void istack_push(istackp p, int v) { p->arr[p->ptr++] = v; }
int istack_pop(istackp p) { return p->arr[--(p->ptr)]; }
int istack_top(istackp p) { return p->arr[p->ptr - 1]; }
