#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "istack.h"

//#define RECUR
#define STACK

void decr12(int n, int k, int *a) {
    if(n < 1) {
        // do nothing
    } else if(n == 1) {
        a[k] = 1;
        int i;
        for(i = 0; i <= k; ++i) {
            printf(" %d", a[i]);
        }
        printf("\n");
    } else {
        a[k] = n;
        decr12(n-1, k+1, a);
        decr12(n-2, k+1, a);
    }
}

void p2(istackp s, int n, int k) {
    istack_push(s, n);
    istack_push(s, k);
}

void decr12_loop(int n, int k, int *a) {
    istackp s = istack_new(100);
    p2(s, n, k);
    while(!istack_isempty(s)) {
        k = istack_pop(s);
        n = istack_pop(s);
        if(n < 1) {
            // do nothing
        } else if(n == 1) {
            a[k] = 1;
            for(int i = 0; i <= k; ++i) {
                printf(" %d", a[i]);
            }
            printf("\n");
        } else {
            a[k] = n;
            p2(s, n-2, k+1);
            p2(s, n-1, k+1);
        }
    }
}

int main(int argc, char *argv[]) {
    int buf[100];
#ifdef RECUR
    decr12(atoi(argv[1]), 0, buf);
#endif
#ifdef STACK
    decr12_loop(atoi(argv[1]), 0, buf);
#endif
    return 0;
}
