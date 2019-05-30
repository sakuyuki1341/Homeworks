#include <stdio.h>
// your iarray_max here
/*===========================================================*
  受けとった配列とその要素数から、配列の最大値を返す関数
　引数として配列の最初のアドレスと、配列の要素数を受け取る
　int型で最大値を戻り値として返している
 *===========================================================*/
int iarray_max(int *a, int n) {
  int max = a[0];
  for(int i = 0; i < n; i++) {
    if(a[i] > max) {
      max = a[i];
    }
  }
  return max;
}

void expect_int(int i1, int i2, char *msg) {
  printf("%s %d:%d %s\n", (i1==i2)?"OK":"NG", i1, i2, msg);
}

int main(void) {
  int a[] = {9,0,0,1,2,3}, b[] = {-1,-3,-2,-4,-1}, c[] = {1,1,1,1,1}, d[] = {1};
  expect_int(iarray_max(a, 6), 9, "9 0 0 1 2 3");
  expect_int(iarray_max(a+1, 5), 3, "0 0 1 2 3");
  expect_int(iarray_max(b, 5), -1, "-1 -3 -2 -4 -1");
  expect_int(iarray_max(c, 5), 1, "1 1 1 1 1");
  expect_int(iarray_max(d, 1), 1, "1");
  return 0;
}
