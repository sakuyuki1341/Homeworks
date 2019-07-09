// radixsort.c --- radixsort (upper->lower) from specified mask
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXDATA 1000000

static int a[MAXDATA];

static void swap(int *a, int i, int j) {
    int x = a[i]; a[i] = a[j]; a[j] = x;
}

static void rs1(int *a, int i, int j, int mask) {
    if(i >= j || mask == 0) { return; }
    int k, s;
    for(s = k = i; k <= j; ++k) {
        if((a[k]&mask) == 0) { swap(a, s++, k); }
    }
    rs1(a, i, s-1, mask/2); rs1(a, s, j, mask/2);
}

static void rs2(int *a, int n) {
    int maxmask = MAXDATA;
    int *b = (int*)(malloc(sizeof(int)*n)); int bc = 0;
    int *c = (int*)(malloc(sizeof(int)*n)); int cc = 0;
    for(int mask = 1; mask < maxmask; mask *= 2) {
        for(int i = 0; i < n; ++i) {
            if((a[i]&mask) == 0) {
                b[bc++] = a[i];
            } else {
                c[cc++] = a[i];
            }
        }
        int ac = 0;
        for(int i = 0; i < bc+1; i++) {
            a[ac++] = b[bc++];
        }
        for(int i = 0; i < cc+1; i++) {
            a[ac++] = c[cc++];
        }
    }
}

void radixsort1(int n, int *a) { rs1(a, 0, n-1, 0x40000000); }

void radixsort2(int n, int *a) { rs2(a, n); }

int makearr();

int main(int argc, char const *argv[]) {
    if(!(argc == 2 && argv[1] > 0)) {
        printf("並び替える数の量を指定してください\n");
        return 0;
    }

    int n = atoi(argv[1]);
    srand(time(NULL));
    struct timespec tm1, tm2;

    for(int i = 0; i < n; ++i) { a[i] = rand()%10000; }

    clock_gettime(CLOCK_REALTIME, &tm1);
    radixsort2(n, a);
    clock_gettime(CLOCK_REALTIME, &tm2);
    for(int i = 0; i < n; ++i) { printf(" %d", a[i]); }
    printf("\n");
    double dt = (tm2.tv_sec-tm1.tv_sec) + 1e-9*(tm2.tv_nsec-tm1.tv_nsec);
    printf("time = %.4f\n", dt);
    return 0;
}
