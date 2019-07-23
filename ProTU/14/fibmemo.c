// fibmemo.c --- calcurate fib with memoization.
#include <stdio.h>
#include <stdlib.h>

#define ARRSIZE 100

int fib(int n) {
    if(n <= 1) {
        return 1;
    }
    return fib(n-1) + fib(n-2);
}

int fib1(int n) {
    static int memo[ARRSIZE];
    if(memo[n] != 0) {
        return memo[n];
    }
    int r = 1;
    if(n > 1) {
        r = fib1(n-1) + fib1(n-2);
    }
    memo[n] = r;
    return r;
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    printf("fib(%d) = %d\n", n , fib1(n));
    return 0;
}
