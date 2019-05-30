#include <stdio.h>
#include <stdlib.h>

// arr: 組み合わせた後の配列
// now: arrにおいて次に代入するべき位置を表記
// str: 与えられた文字の配列
// insert: strにおいて次に代入する文字の位置を表記
// count: 残り代入しなくてはいけない文字数

// 	vol: 文字の配列の要素数
int vol;

void combine(char *arr, int now, char *str, int insert, int count) {
  if(count == 0) {
		arr[now++] = str[insert];
		arr[now] = '\0';
    printf("%s\n", arr + 1);
    return;
  }

	arr[now++] = str[insert];
	count--;
  for(int i = 0; i < vol; i++) {
    combine(arr, now, str, i, count);
  }

}

// argv: 文字の配列、その要素数、生成する長さ

int main(int argc, char *argv[]) {
  vol = atoi(argv[2]);
  int count = atoi(argv[3]);
  int now = 0, insert = 0;
  char arr[256];
  combine(arr, now, argv[1], insert, count);
  return 0;
}
