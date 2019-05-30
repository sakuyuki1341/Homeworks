#include <stdio.h>

int main(void) {
  int a, b, n, i, pre_sei, pre_kyo;
  scanf("%d %d ", &a, &b);
  scanf("%d ", &n);
  int sei = a;
  int kyo = b;
  for(i = 0; i < n - 1; i++) {
    pre_sei = sei*a - kyo*b;
    pre_kyo = sei*b + kyo*a;
    sei = pre_sei;
    kyo = pre_kyo;
  }
  printf("%d %d\n", sei, kyo);
  return 0;
}
