// pqueue.c --- pointer type queue impl. with array
#include <stdlib.h>
#include "pqueue.h"
struct pqueue { int ip, op, size; void **arr; };
pqueuep pqueue_new(int size) {
  pqueuep p = (pqueuep)malloc(sizeof(struct pqueue));
  p->ip = p->op = 0; p->size = size;
  p->arr = (void**)malloc(size * sizeof(void*)); return p;
}
bool pqueue_isempty(pqueuep p) { return p->ip == p->op; }
bool pqueue_isfull(pqueuep p) { return (p->ip+1)%p->size == p->op; }
void pqueue_enq(pqueuep p, void *v) {
  if(pqueue_isfull(p)) { return; }
  p->arr[p->ip++] = v; if(p->ip >= p->size) { p->ip = 0; }
}
void *pqueue_deq(pqueuep p) {
  if(pqueue_isempty(p)) { return 0; }
  void *v = p->arr[p->op++]; if(p->op >= p->size) { p->op = 0; }
  return v;
}
