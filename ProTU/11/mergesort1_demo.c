// mergesort1demo.c --- demonstration of mergesort1.
// sortdemo.c --- demonstration for basic sort.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pqueue.h"

#define MAXDATA 1000000

// #define ENSHU_EX
 #define ENSHU_4_FT
// #define ENSHU_4_ST
// #define ENSHU_4_TT

static int a[MAXDATA];

int *ivec_new(int size) {
  int *a = (int*)malloc((size+1) * sizeof(int));
  a[0] = size; return a;
}
// mergesort-----------------------------------------------
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

// quicksort-----------------------------------------------
static void iswap(int *a, int i, int j) {
  int x = a[i]; a[i] = a[j]; a[j] = x;
}

void qs(int *a, int i, int j) {
  if(j <= i) { return; }
  int s = i, pivot = a[j];
  for(int k = i; k < j; ++k) {
    if(a[k] < pivot) { iswap(a, s++, k); }
  }
  iswap(a, j, s); qs(a, i, s-1); qs(a, s+1, j);
}

void quicksort(int *a, int n) { qs(a, 0, n-1); }

// quicksort_adv-------------------------------------------
int med (int x, int y, int z) {
    if(a[x] > a[y]) {
        if(a[y] > a[z]){ return y; }
        else if(a[z] > a[x]) { return x; }
        else { return z; }
    } else {
        if(a[x] > a[z]) { return x; }
        else if(a[z] > a[y]) { return y; }
        else { return z; }
    }
}
void qs_adv(int* a, int i, int j) {
    if(j <= i) { return; }
    int s = i, pivot = a[med(i, (i+j)/2, j)];
    for(int k = i; k < j; ++k) {
      if(a[k] < pivot) { iswap(a, s++, k); }
    }
    iswap(a, j, s); qs(a, i, s-1); qs(a, s+1, j);
  }

 void quicksort_adv(int *a, int n) { qs_adv(a, 0, n-1); }

// use_queue-----------------------------------------------
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

// main----------------------------------------------------
#ifdef ENSHU_EX
int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  srand(time(NULL));
  for(int i = 0; i < n; ++i) { a[i] = rand()%10000; }
  mergesort1(a, n);
  for(int i = 0; i < n; ++i) { printf(" %d", a[i]); }
  printf("\n");
  return 0;
}
#endif
#ifdef ENSHU_4_FT
int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  srand(time(NULL));
  struct timespec tm1, tm2;
  for(int i = 0; i < n; ++i) { a[i] = rand()%10000; }
  clock_gettime(CLOCK_REALTIME, &tm1);
  quicksort(a, n);
  clock_gettime(CLOCK_REALTIME, &tm2);
  for(int i = 0; i < n; ++i) { printf(" %d", a[i]); }
  printf("\n");
  double dt = (tm2.tv_sec-tm1.tv_sec) + 1e-9*(tm2.tv_nsec-tm1.tv_nsec);
  printf("time = %.4f\n", dt);
  return 0;
}
#endif
#ifdef ENSHU_4_ST
int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  srand(time(NULL));
  struct timespec tm1, tm2;
  for(int i = 0; i < n; ++i) { a[i] = i; }
  clock_gettime(CLOCK_REALTIME, &tm1);
  quicksort(a, n);
  clock_gettime(CLOCK_REALTIME, &tm2);
  for(int i = 0; i < n; ++i) { printf(" %d", a[i]); }
  printf("\n");
  double dt = (tm2.tv_sec-tm1.tv_sec) + 1e-9*(tm2.tv_nsec-tm1.tv_nsec);
  printf("time = %.4f\n", dt);
  return 0;
}
#endif
#ifdef ENSHU_4_TT
int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  srand(time(NULL));
  struct timespec tm1, tm2;
  for(int i = 0; i < n; ++i) { a[i] = i; }
  clock_gettime(CLOCK_REALTIME, &tm1);
  quicksort_adv(a, n);
  clock_gettime(CLOCK_REALTIME, &tm2);
  for(int i = 0; i < n; ++i) { printf(" %d", a[i]); }
  printf("\n");
  double dt = (tm2.tv_sec-tm1.tv_sec) + 1e-9*(tm2.tv_nsec-tm1.tv_nsec);
  printf("time = %.4f\n", dt);
  return 0;
}
#endif
