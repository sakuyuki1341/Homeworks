// test_iset.c
#include <stdbool.h>
#include <stdio.h>
#include "iset.h"

//#define ENSHU_EX
//#define ENSHU_1
#define ENSHU_2

void expect_iset(isetp s, int m, int n, int a[], char *msg) {
    bool ok = true; int p = 0;
    for(int i = 0; i <= m; ++i) {
        if(p < n && i == a[p]) {
            ++p;
            if(!iset_isin(s, i)) { printf(" NG: %d not in set.\n", i); ok = false; }
        } else {
            if(iset_isin(s, i)) { printf(" NG: %d in set.\n", i); ok = false; }
        }
    }
    printf("%s %s\n", ok?"OK":"NG", msg);
}

int main(void) {
#ifdef  ENSHU_EX
    int a[] = { 1, 3, 5, 7 };
    isetp s = iset_new();
    iset_addelt(s, 1); iset_addelt(s, 3); iset_addelt(s, 5);
    expect_iset(s, 9, 3, a, "initial: { 1 3 5 }"); iset_subelt(s, 1);
    expect_iset(s, 9, 2, a+1, "- { 1 }: { 3 5 }");
    isetp q = iset_new(); iset_addelt(s, 7); iset_addelt(s, 5);
    isetp r = iset_union(s, q);
    expect_iset(r, 9, 3, a+1, "+ { 7 5 }: { 3 5 7 }");
    iset_free(s); iset_free(q); iset_free(r);
#endif
#ifdef ENSHU_1
    int a[] = { 1, 3 };
    isetp s = iset_new();
    iset_addelt(s, 1); iset_addelt(s, 3); iset_addelt(s, 5);
    isetp t = iset_new();
    iset_addelt(t, 1); iset_addelt(t, 2); iset_addelt(t, 3);
    isetp r = iset_intersection(s, t);
    expect_iset(r, 9, 2, a, "{ 1 3 }");
    iset_free(s); iset_free(t); iset_free(r);
#endif
#ifdef ENSHU_2
    int a[] = { 5 };
    isetp s = iset_new();
    iset_addelt(s, 1); iset_addelt(s, 3); iset_addelt(s, 5);
    isetp t = iset_new();
    iset_addelt(t, 1); iset_addelt(t, 2); iset_addelt(t, 3);
    isetp r = iset_difference(s, t);
    expect_iset(r, 9, 1, a, "{ 5 }");
    iset_free(s); iset_free(t); iset_free(r);
#endif
    return 0;
}
