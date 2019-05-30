#include <stdio.h>
#include <stdbool.h>
// your iarray_sort here
/*=====================================================================*
  受け取った配列の指定された位置と、その一個右の位置を交換する関数
　引数としては、位置を交換したい配列の先頭のアドレスと、
　交換したい配列のアドレスを受け取る
　戻り値はなし
 *=====================================================================*/
void swap_front(int *a, int i) {
  int front_save = a[i];
  a[i] = a[i + 1];
  a[i + 1] = front_save;
}
/*=====================================================================*
  受け取った配列の指定された位置と、その一個左の位置を交換する関数
　引数としては、位置を交換したい配列の先頭のアドレスと、
　交換したい配列のアドレスを受け取る
　戻り値はなし
 *=====================================================================*/
void swap_back(int *a, int i) {
  int front_save = a[i];
  a[i] = a[i - 1];
  a[i - 1] = front_save;
}

int iarray_max(int *a, int n) {
  int max = a[0];
  for(int i = 0; i < n; i++) {
    if(a[i] > max) {
      max = a[i];
    }
  }
  return max;
}
/*=====================================================================*
  受け取った配列をアルゴリズム「バブルソート」に基づいてソートする関数
　引数としては、ソートしたい配列の先頭アドレスと、その配列の要素数を受け取る
　戻り値はなし
 *=====================================================================*/
void iarray_sort(int *a, int n) {
  int max_save = iarray_max(a, n);
  int i;
  int max;
  while(1) {
    max = a[0];
    i = 0;
    for(; i < n; i++) {
      if(max > a[i]) {
        swap_back(a, i);
	 break;
      } else {
	 max = a[i];
       } 
     }
    if(i == n) {
      break;
    }
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
  int a[] = {8,5,2,4,1}, b[] = {1,2,4,5,8}; 
  iarray_sort(a, 5); expect_iarray(a, b, 5, "85241 -> 12458");
  return 0;
}
