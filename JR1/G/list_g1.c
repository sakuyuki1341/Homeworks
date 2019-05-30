#include <stdio.h>

void sort3(int* ap, int* bp, int* cp);

int main(void) {
  int a, b, c;
  scanf("%d %d %d", &a, &b, &c);
  sort3(&a, &b, &c);
  printf("%d %d %d\n", a, b, c);
  return 0;
}

void sort3(int* ap, int* bp, int* cp) {
  int a = *ap;
  int b = *bp;
  int c = *cp;
  if(a <= b) {
    if(b <= c) {
      //a<=b<=c
      *ap = a;
      *bp = b;
      *cp = c;
    } else if(c <= a) {
      //c<=a<=b
      *ap = c;
      *bp = a;
      *cp = b;
    } else {
      //a<=c<=b
      *ap = a;
      *bp = c;
      *cp = b;
    }
  } else {
    if(a <= c) {
      //b<=a<=c
      *ap = b;
      *bp = a;
      *cp = c;
    } else if(c <= b) {
      //c<=b<=a
      *ap = c;
      *bp = b;
      *cp = a;
    } else {
      //b<=c<=a
      *ap = b;
      *bp = c;
      *cp = a;
    }
  }
}
