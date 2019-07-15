// quicksort.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define ENSHU_4_FT
// #define ENSHU_4_ST
// #define ENSHU_4_TT

// quicksort (normal)--------------------------------------
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

void quicksort(int n, int* a) { qs(a, 0, n-1); }

// quicksort_adv-------------------------------------------
int med (int* a, int x, int y, int z) {
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
    int s = i, pivot = a[med(a, i, (i+j)/2, j)];
    for(int k = i; k < j; ++k) {
      if(a[k] < pivot) { iswap(a, s++, k); }
    }
    iswap(a, j, s); qs(a, i, s-1); qs(a, s+1, j);
  }

void quicksort_adv(int n, int* a) { qs_adv(a, 0, n-1); }


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

void expect_sort_iarray_sorted(int n, void (*f)(int m, int *a), char *msg) {
  int c = 0, *a = (int*)malloc(n * sizeof(int));
  srand(time(NULL));
  for(int i = 0; i < n; ++i) { a[i] = i; }
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


int main(int argc, char const *argv[]) {
    if(!(argc == 2 && argv[1] > 0)) {
        printf("並び替える数の量を指定してください\n");
        return 0;
    }

    int n = atoi(argv[1]);
#ifdef ENSHU_4_FT
    expect_sort_iarray(n, quicksort, "quicksort(first_time)");
#endif
#ifdef ENSHU_4_ST
    expect_sort_iarray_sorted(n, quicksort, "quicksort(second_time)");
#endif
#ifdef ENSHU_4_TT
    expect_sort_iarray_sorted(n, quicksort_adv, "quicksort_adv(third_time)");
#endif
    return 0;
}
