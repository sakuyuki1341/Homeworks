#include <stdlib.h>
#include "iqueue.h"
struct iqueue { int ip, op, size; int *arr; };
iqueuep iqueue_new(int size) {
  iqueuep p = (iqueuep)malloc(sizeof(struct iqueue));
  p->ip = p->op = 0; p->size = size;
  p->arr = (int*)malloc(size * sizeof(int)); return p;
}
bool iqueue_isempty(iqueuep p) { return p->ip == p->op; }
bool iqueue_isfull(iqueuep p) { return (p->ip+1)%p->size == p->op; }
void iqueue_enq(iqueuep p, int v) {
  if(iqueue_isfull(p)) { return; }
  p->arr[p->ip++] = v; if(p->ip >= p->size) { p->ip = 0; }
}
int iqueue_deq(iqueuep p) {
  if(iqueue_isempty(p)) { return 0; }
  int v = p->arr[p->op++]; if(p->op >= p->size) { p->op = 0; }
  return v;
}
