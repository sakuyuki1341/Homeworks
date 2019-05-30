#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void iarray_read(int *a, int n) {
  for(int i = 0; i < n; ++i) {
    printf("%d> ", i+1); scanf("%d", a+i);
  }
}

bool iarray_equal(int *a, int *b, int n) {
  for(int i = 0; i < n; ++i) {
    if(a[i] != b[i]) {return false;}
  }
  return true;
}

void iarray_print(int *a, int n) {
  for(int i = 0; i < n; ++i) { printf(" %2d", a[i]); }
  printf("\n");
}

void expect_iarray(int *a, int *b, int n, char *msg) {
  printf("%s %s\n", iarray_equal(a, b, n)?"OK":"NG", msg);
  iarray_print(a, n); iarray_print(b, n);
}

int *ivec_new(int size) {
  int *a = (int*)malloc((size+1) * sizeof(int));
  a[0] = size; return a;
}

void ivec_read(int *a) { iarray_read(a+1, a[0]); }

void ivec_print(int *a) { iarray_print(a+1, a[0]); }

int *ivec_concat(int *a, int *b) {
  int *c = ivec_new(a[0]+b[0]);
  for(int i = 1; i <= a[0]; ++i) { c[i] = a[i]; }
  for(int i = 1; i <= b[0]; ++i) { c[i + a[0]] = b[i]; }
  return c;
}

int *ivec_reverse(int *a) {
  int *b = ivec_new(a[0]);
  for(int i = 0; i < a[0]; i++) {
    b[i + 1] = a[a[0] - i];
  }
  return b;
}
/*
int main(void) {
  int *a, *b, *c;
  a = ivec_new(3); ivec_read(a);
  b = ivec_new(2); ivec_read(b);
  c = ivec_concat(b, a); ivec_print(c);
  free(a); free(b); free(c);
  return 0;
}
*/
int main(void) {
  int a[] = {3,1,2,3}, b[] = {3,3,2,1}, c[] = {1,1}, d[] = {1,1};
  int *p = ivec_reverse(a);
  int *q = ivec_reverse(c);
  expect_iarray(p, b, 4, "{1,2,3} -> {3,2,1}");
  expect_iarray(q, d, 2, "{1} -> {1}");
  return 0;
}
