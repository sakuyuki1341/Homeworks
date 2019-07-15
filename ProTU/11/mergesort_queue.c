// mergesort1demo.c --- demonstration of mergesort1.
// sortdemo.c --- demonstration for basic sort.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pqueue.h"

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

void mergesort_queue(int n, int* a) {
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

void expect_sort_iarray(int n, void (*f)(int m, int *a), char *msg) {
  int c = 0, *a = (int*)malloc(n * sizeof(int));
  srand(time(NULL));
  for(int i = 0; i < n; ++i) { a[i] = rand()%10000; }
  struct timespec tm1, tm2;
  clock_gettime(CLOCK_REALTIME, &tm1);
  (*f)(n, a);
  clock_gettime(CLOCK_REALTIME, &tm2);
  for(int i = 1; i < n; ++i) {
    if(a[i-1] <= a[i]) { continue; } // correct order
    if(++c < 5) {
      printf("  wrong order at %d: %d > %d\n", i-1, a[i-1], a[i]);
    } else if(c == 5) {
      printf("  more wrong place omitted.\n");
    }
  }
  double dt = (tm2.tv_sec-tm1.tv_sec) + 1e-9*(tm2.tv_nsec-tm1.tv_nsec);
  printf("%s time=%.4f %s\n", c==0?"OK":"NG", dt, msg); free(a);
}

int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  expect_sort_iarray(n, mergesort_queue, "mergesort");
  return 0;
}
