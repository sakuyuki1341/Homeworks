#include <stdio.h>
#include <stdbool.h>

/*============================================================================*
  引数として受け取った配列の並び順を逆順にする関数
  引数として、配列の先頭のアドレスと、配列の要素数を受け取る
  返り値はない
 *============================================================================*/
void iarray_revese(int *a, int n) {
  int save[n];
  for(int i = 0; i < n; ++i) {
    save[i] = a[i];
  }
  for(int i = 0; i < n; ++i) {
    a[i] = save[n-i-1];
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
  int a[] = {8,5,2,4,1}, b[] = {1,4,2,5,8};
  iarray_revese(a, 5); expect_iarray(a, b, 5, "85241 -> 14258");
  return 0;
}
