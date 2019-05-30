#include <stdlib.h>
#include "iqueue_1_a.h"
struct iqueue { int ip, op, size, count; int *arr; };

iqueuep iqueue_new(int size) {
  iqueuep p = (iqueuep)malloc(sizeof(struct iqueue));
  p->ip = p->op = p->count = 0; p->size = size;
  p->arr = (int*)malloc(size * sizeof(int)); return p;
}

bool iqueue_isempty(iqueuep p) { return p->count == 0; }

bool iqueue_isfull(iqueuep p) { return p->count == p->size; }

void iqueue_enq(iqueuep p, int v) {
  if(iqueue_isfull(p)) {
    iqueue_deq(p);
  }
  p->arr[p->ip++] = v;
  if(p->ip >= p->size) { p->ip = 0; }
  p->count += 1;
}

int iqueue_deq(iqueuep p) {
  if(iqueue_isempty(p)) { return 0; }
  int v = p->arr[p->op++];
  if(p->op >= p->size) { p->op = 0; }
  p->count -= 1;
  return v;
}

int iqueue_count(iqueuep p) {
  return p->count;
}

int iqueue_op(iqueuep p) {
  if(iqueue_isempty(p)) {
    return 0;
  }
  return p->arr[p->op];
}
