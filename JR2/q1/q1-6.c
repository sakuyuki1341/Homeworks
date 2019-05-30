#include<stdio.h>
#include<stdlib.h>

typedef struct {
  int n, d; // n: 分子, d: 分母
} rational;

int gcd ( int a, int b )
{
  int amari = 1;
  while(amari != 0) {
    amari = a % b;
    a = b;
    b = amari;
  }
  return a;
}

rational yakubu(rational z) {
  int yaku = gcd(z.n, z.d);
  z.n = z.n / yaku;
  z.d = z.d / yaku;
  return z;
}

rational setr(int n, int d)
{
  rational z;
  if (d == 0) {
    fprintf(stderr, "Denominator must be nonzero.\n");
    exit(1);
  }
  z.n = n;
  z.d = d;
  return z;
}

void printr(rational z)
{
  printf("%d/%d\n", z.n, z.d);
}

rational mulr(rational x, rational y)
{
  int n = x.n * y.n;
  int d = x.d * y.d;
  rational z = setr(n, d);
  return z;
}

rational addr(rational x, rational y)
{
  int n = x.n * y.d + y.n * x.d;
  int d = x.d * y.d;
  rational z = setr(n, d);
  return z;
}

rational reductionr(int n, rational ary[])
{
  rational ret = addr(ary[0], ary[1]);
  n -= 2;
  int i = 2;
  while(n > 0) {
    ret = addr(ret, ary[i]);
    i++;
    n--;
  }
  ret = yakubu(ret);
  return ret;
}

void example6(void)
{
  rational ary[3];
  ary[0] = setr(1, 2);
  ary[1] = setr(2, 3);
  ary[2] = setr(3, 4);
  rational z = reductionr(3, ary);
  printr(z);
}

void check5(int argc, char *argv[])
{
  int n = atoi(argv[1]);
  rational ary[n];
  for(int i = 0; i < n; i++) {
    ary[i] = setr(atoi(argv[2+i*2]), atoi(argv[3+i*2]));
  }
  rational z = reductionr(n, ary);
  printr(z);
}

int main(int argc, char *argv[])
{
  // example6();
  check5(argc, argv);
  return 0;
}
