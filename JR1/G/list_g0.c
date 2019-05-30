#include <stdio.h>

void swap(int *ap, int *bp);

int main(void) {
  int a, b;
  scanf("%d %d", &a, &b);
  swap(&a, &b);
  printf("%d %d\n", a, b);
  return 0;
}

void swap(int *ap, int *bp) {
  int t = *ap;
  *ap = *bp;
  *bp = t;
  return;
}
