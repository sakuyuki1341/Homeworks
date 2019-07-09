// radixsort.c --- radixsort (upper->lower) from specified mask
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXDATA 10000

static int arr_f[MAXDATA];

static void swap(int *a, int i, int j) {
    int x = a[i]; a[i] = a[j]; a[j] = x;
}

static void rs(int *a, int i, int j, int mask) {
    if(i >= j || mask == 0) { return; }
    int k, s;
    for(s = k = i; k <= j; ++k) {
        if((a[k]&mask) == 0) { swap(a, s++, k); }
    }
    rs(a, i, s-1, mask/2); rs(a, s, j, mask/2);
}

void radixsort(int n, int *a) { rs(a, 0, n-1, 0x40000000); }

int makearr();

int main(int argc, char const *argv[]) {
    if(!(argc == 2 && argv[1] > 0)) {
        printf("並び替える数の量を指定してください\n");
        return 0;
    }

    int n = atoi(argv[1]);
    srand(time(NULL));
    struct timespec tm1, tm2;

    for(int i = 0; i < n; ++i) { arr_f[i] = rand()%2; }

    clock_gettime(CLOCK_REALTIME, &tm1);
    radixsort(n, arr_f);
    clock_gettime(CLOCK_REALTIME, &tm2);
    for(int i = 0; i < n; ++i) { printf(" %d", arr_f[i]); }
    printf("\n");
    double dt = (tm2.tv_sec-tm1.tv_sec) + 1e-9*(tm2.tv_nsec-tm1.tv_nsec);
    printf("time = %.4f\n", dt);
    return 0;
}
