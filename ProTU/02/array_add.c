#include <stdio.h>
#include <stdbool.h>
// your iarray_add here
/*=============================================================================*
　2つの長さが同じ配列を受け取り、
　2番目の各要素の値を1番目の配列の各要素に足し込む関数
　引数として、2つの配列の先頭アドレスと、配列の長さを受け取る
　戻り値は存在しない
 *=============================================================================*/
void iarray_add(int *a, int *b, int n) {
  for(int i = 0; i < n; i++) {
    a[i] += b[i];
  }
}

bool iarray_equal(int *a, int *b, int n) {
  for(int i = 0; i < n; ++i) {
    if(a[i] != b[i]) { return false; }
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
int main(void) {
  int a[] = {8,5,2,4,1}, b[] = {1,1,2,2,3}, c[] = {9,6,4,6,4};
  iarray_add(a, b, 5); expect_iarray(a, c, 5, "85241+11223 -> 96464");
  return 0;
}
