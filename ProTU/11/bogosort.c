// bogosort.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAXDATA 1000000

static int a[MAXDATA];

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
        for(int i = 1; i < n; i++) {
            swap(a, (rand() % (n-i))+i, i-1);
        }
    }
}

void bogosort(int* a, int n) {
    bs(a, n);
}

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
    bogosort(a, n);
    clock_gettime(CLOCK_REALTIME, &tm2);
    for(int i = 0; i < n; ++i) { printf(" %d", a[i]); }
    printf("\n");
    double dt = (tm2.tv_sec-tm1.tv_sec) + 1e-9*(tm2.tv_nsec-tm1.tv_nsec);
    printf("time = %.4f\n", dt);
    return 0;
}
