// isetdemo1.c
#include <stdio.h>
#include <stdbool.h>
#include "iset.h"

isetp readiset(void) {
    isetp s = iset_new();
    while(true) {
        int i; printf("i> "); scanf("%d", &i);
        if(i < 0) { return s; } else { iset_addelt(s, i); }
    }
}

void printiset(isetp s) {
    printf("{");
    for(int max = iset_max(s), i = 0; i <= max; ++i) {
        if(iset_isin(s, i)) { printf(" %d", i); }
    }
    printf(" }\n");
}

int main(void) {
    isetp s = readiset(); printiset(s);
    isetp t = readiset(); printiset(t);
    isetp u = iset_union(s, t); printiset(u);
    iset_free(s); iset_free(t); iset_free(u);
    return 0;
}
