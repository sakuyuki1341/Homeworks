// iset_1.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "iset.h"
#define MAXARRAY 10000
struct iset { int size, *a; };

isetp iset_new() {
    isetp s = (isetp)malloc(sizeof(struct iset));
    s->size = 0; s->a = (int*)malloc(sizeof(int)*MAXARRAY);
    return s;
}

void iset_free(isetp s) { free(s->a); free(s); }

static int isin1(isetp s, int e) {
    for(int i = 0; i < s->size; ++i) {
        if(s->a[i] == e) { return i; }
    }
    return -1;
}

bool iset_isempty(isetp s) { return s->size == 0; }

bool iset_isin(isetp s, int e) { return isin1(s, e) >= 0; }

static int max2(int a, int b) { return (a > b) ? a : b; }

int iset_max(isetp s) {
    int max = 0;
    for(int i = 0; i < s->size; ++i) { max = max2(max, s->a[i]); }
    return max;
}

void iset_addelt(isetp s, int e) {
    if(iset_isin(s, e) || s->size >= MAXARRAY-1) { return; }
    s->a[(s->size)++] = e;
}

void iset_subelt(isetp s, int e) {
    int i = isin1(s, e); if(i < 0) { return; }
    s->a[i] = s->a[--(s->size)];
}

isetp iset_union(isetp s, isetp t) {
    isetp u = iset_new();
    for(int i = 0; i < s->size; ++i) { iset_addelt(u, s->a[i]); }
    for(int i = 0; i < t->size; ++i) {
        if(!iset_isin(s, t->a[i])) { iset_addelt(u, t->a[i]); }
    }
    return u;
}

isetp iset_intersection(isetp s, isetp t) {
    isetp i = iset_new();
    for(int j = 0; j < s->size; j++) {
        for(int k = 0; k < t->size; k++) {
            if(s->a[j] == t->a[k]) {
                iset_addelt(i, s->a[j]);
            }
        }
    }
    return i;
}

/*========================================================*
 * 関数iset_difference(isetp s, isetp t): 集合sから集合t
 * を引いた集合dを返す
 *========================================================*/
isetp iset_difference(isetp s, isetp t) {
    isetp d = iset_new();
    for(int i = 0; i < s->size; i++) {
        if(!iset_isin(t, s->a[i])) {
            iset_addelt(d, s->a[i]);
        }
    }
    return d;
}
