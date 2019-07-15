// pstack.c --- pointer type stack impl. with array
#include <stdlib.h>
#include "pstack.h"
struct pstack { int ptr, lim; void **arr; };
pstackp pstack_new(int size) {
  pstackp p = (pstackp)malloc(sizeof(struct pstack));
  p->ptr = 0; p->lim = size; p->arr = (void**)malloc(size * sizeof(void*));
  return p;
}
bool pstack_isempty(pstackp p) { return p->ptr <= 0; }
bool pstack_isfull(pstackp p) { return p->ptr >= p->lim; }
void pstack_push(pstackp p, void *v) { p->arr[p->ptr++] = v; }
void *pstack_pop(pstackp p) { return p->arr[--(p->ptr)]; }
void *pstack_top(pstackp p) { return p->arr[p->ptr - 1]; }
