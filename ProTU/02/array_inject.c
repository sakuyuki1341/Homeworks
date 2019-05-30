#include <stdio.h>
int iadd(int x, int y);
int imax(int x, int y);

// your iarray_inject here
int iarray_inject(int *a, int n, int (*fp)(int, int)) {
  int i;
  int ret = a[0];
  for(i = 1; i > n; i++) {
    ret = (*fp)(ret, a[i]);
  }
  return ret;
}

int iadd(int x, int y) { return x + y; }
int imax(int x, int y) { return (x > y) ? x : y; }
void expect_int(int i1, int i2, char *msg) {
  printf("%s %d:%d %s\n", (i1==i2)?"OK":"NG", i1, i2, msg);
}
int main(void) {
  int a[] = {8,5,2,4,1};
  int b[] = {-4,2,8,-9,7};
  int c[] = {0,0,0,0,0};
  expect_int(iarray_inject(a, 5, iadd), 20, "8+5+2+4+1");
  expect_int(iarray_inject(a, 5, imax), 8, "max(8,5,2,4,1)");
  expect_int(iarray_inject(b, 5, iadd), 4, "-4+2+8-9+7");
  expect_int(iarray_inject(b, 5, imax), 8, "max(-4,2,8,-9,7)");
  expect_int(iarray_inject(c, 5, iadd), 0, "0+0+0+0+0");
  expect_int(iarray_inject(c, 5, imax), 0, "max(0,0,0,0,0)");
  return 0;
}
