// bstree.c --- itbl impl with binary search tree.
#include <stdlib.h>
#include <stdio.h>
#include "itbl.h"

// #define RECURF
#define LOOPF

typedef struct ent *entp;
struct ent { int key, val; entp left, right; };
struct itbl { entp root; };
itblp itbl_new() {
  itblp p = (itblp)malloc(sizeof(struct itbl));
  p->root = NULL; return p;
}

#ifdef RECURF
static int get(entp p, int k) {
  if(p == NULL) { return -1; }
  if(k == p->key) { return p->val; }
  return get((k < p->key) ? p->left : p->right, k);
}
#endif
#ifdef LOOPF
static int get(entp p, int k) {
    while(1) {
        if(p == NULL) { return -1; }
        if(k == p->key) { return p->val; }
        if(k < p->key) {
            p = p->left;
        } else {
            p = p->right;
        }
    }
}
#endif

int itbl_get(itblp p, int k) { return get(p->root, k); }

static void put(entp *p, int k, int v) {
  if(*p == NULL) {
    entp q = *p = (entp)malloc(sizeof(struct ent));
    q->left = q->right = NULL; q->key = k; q->val = v;
  } else if(k == (*p)->key) {
    (*p)->val = v;
  } else {
    put((k < (*p)->key) ? &((*p)->left) : &((*p)->right), k, v);
  }
}

void itbl_put(itblp p, int k, int v) { put(&(p->root), k, v); }
static void pr(entp p) {
  if(p->left != NULL) { printf("("); pr(p->left); printf(") "); }
  printf("%d:%d", p->key, p->val);
  if(p->right != NULL) { printf(" ("); pr(p->right); printf(")"); }
}

void itbl_pr(itblp p) {
  if(p->root != NULL) { printf("("); pr(p->root); printf(")\n"); }
}
