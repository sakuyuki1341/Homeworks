// mergesort_stack.c --- test mergesort of stack
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pstack.h"

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

void mergesort_stack(int n, int* a) {
  pstackp s = pstack_new(n+1);
  int *v, *w;
  for(int i = 0; i < n; ++i) {
    v = ivec_new(1); v[1] = a[i]; pstack_push(s, v);
  }
  while(true) {
    v = (int*)pstack_pop(s); if(pstack_isempty(s)) { break; }
    w = (int*)pstack_pop(s); pstack_push(s, ivec_merge(v, w));
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
  expect_sort_iarray(n, mergesort_stack, "mergesort");
  return 0;
}
