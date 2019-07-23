// fibmemo.c --- calcurate fib with memoization.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRSIZE 100

int pow3(int n) {
    if(n <= 0) {
        return 1;
    }
    return pow3(n-1) + pow3(n-1) + pow3(n-1);
}

int pow3_1(int n) {
    static int memo[ARRSIZE];
    if(memo[n] != 0) {
        return memo[n];
    }
    int r = 1;
    if(n >= 1) {
        r = pow3_1(n-1) + pow3_1(n-1) + pow3_1(n-1);
    }
    memo[n] = r;
    return r;
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    struct timespec tm1, tm2, tm3, tm4;
    clock_gettime(CLOCK_REALTIME, &tm1);
    int not_usememo = pow3(n);
    clock_gettime(CLOCK_REALTIME, &tm2);
    clock_gettime(CLOCK_REALTIME, &tm3);
    int usememo = pow3_1(n);
    clock_gettime(CLOCK_REALTIME, &tm4);
    double not_usedt = (tm2.tv_sec-tm1.tv_sec) + 1e-9*(tm2.tv_nsec-tm1.tv_nsec);
    printf("not_usememo: pow3(%d)=%d, time=%.4f\n", n , not_usememo, not_usedt);
    double usedt = (tm4.tv_sec-tm3.tv_sec) + 1e-9*(tm4.tv_nsec-tm3.tv_nsec);
    printf("usememo: pow3(%d)=%d, time=%.4f\n", n , usememo, usedt);
    return 0;
}
