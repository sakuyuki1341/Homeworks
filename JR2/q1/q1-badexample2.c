#include<stdio.h>

typedef struct {
  int n, d; // n: 分子, d: 分母
} rational;

rational setr(int n, int d)
{
  rational z;
  z.n = n;
  z.d = d;
  return z;
}

void printr(rational z)
{
  printf("%d/%d\n", z.n, z.d);
}

void badexample2(void)
{
  rational z = setr(1, 3); // r = 1/3
  int a = 1;
  int b = z * a; // 1/3 * 3 = 1???
  printf("%d\n", b); // -> ???
}

int main(int argc, char *argv[])
{
  badexample2();
  return 0;
}

