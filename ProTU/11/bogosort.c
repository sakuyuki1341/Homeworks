// bogosort.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

static void swap(int *a, int i, int j) {
    int x = a[i]; a[i] = a[j]; a[j] = x;
}

static bool is_sorted(int* a, int n) {
    bool flag_yes = true;
    for(int i = 0; i < n-1; i++) {
        if(a[i] > a[i+1]) {
            flag_yes = false;
        }
    }
    return flag_yes;
}

static void bs(int* a, int n) {
    while (!is_sorted(a, n)) {
        for(int i = 0; i < n; i++) {
            swap(a, (rand() % (n-i))+i, i);
        }
    }
}

void bogosort(int* a, int n) {
    bs(a, n);
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

int main(int argc, char const *argv[]) {
    if(!(argc == 2 && argv[1] > 0)) {
        printf("並び替える数の量を指定してください\n");
        return 0;
    }

    int n = atoi(argv[1]);
    expect_sort_iarray(n, bogosort, "bogosort");
    return 0;
}
