// mergesort1demo.c --- demonstration of mergesort1.
// sortdemo.c --- demonstration for basic sort.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pqueue.h"
#define MAXDATA 1000000
static int a[MAXDATA];

int *ivec_new(int size) {
  int *a = (int*)malloc((size+1) * sizeof(int));
  a[0] = size; return a;
}

int *ivec_merge(int *b, int *c) {
  int ib = 1, ic = 1, ia = 1, *a = ivec_new(b[0]+c[0]);
  while(ia <= a[0]) {
    if(ib > b[0])          { a[ia++] = c[ic++]; }
    else if(ic > c[0])     { a[ia++] = b[ib++]; }
    else if(c[ic] < b[ib]) { a[ia++] = c[ic++]; }
    else                   { a[ia++] = b[ib++]; }
  }
  return a;
}

void mergesort1(int *a, int n) {
  pqueuep q = pqueue_new(n+1);
  int *v, *w;
  for(int i = 0; i < n; ++i) {
    v = ivec_new(1); v[1] = a[i]; pqueue_enq(q, v);
  }
  while(true) {
    v = (int*)pqueue_deq(q); if(pqueue_isempty(q)) { break; }
    w = (int*)pqueue_deq(q); pqueue_enq(q, ivec_merge(v, w));
    free(v); free(w);
  }
  for(int i = 0; i < n; ++i) { a[i] = v[i+1]; }
}

int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  srand(time(NULL));
  for(int i = 0; i < n; ++i) { a[i] = rand()%10000; }
  mergesort1(a, n);
  for(int i = 0; i < n; ++i) { printf(" %d", a[i]); }
  printf("\n");
  return 0;
}
