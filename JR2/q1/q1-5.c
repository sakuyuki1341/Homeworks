#include<stdio.h>
#include<stdlib.h>

typedef struct {
  int n, d; // n: 分子, d: 分母
} rational;

int gcd ( int a, int b ) {
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

rational setr(int n, int d) {
  rational z;
  if (d == 0) {
    fprintf(stderr, "Denominator must be nonzero.\n");
    exit(1);
  }
  z.n = n;
  z.d = d;
  z = yakubu(z);
  return z;
}

void printr(rational z) {
    printf("%d/%d\n", z.n, z.d);
}

rational mulr(rational x, rational y) {
  int n = x.n * y.n;
  int d = x.d * y.d;
  rational z = setr(n, d);
  z = yakubu(z);
  return z;
}

rational addr(rational x, rational y) {
  int n = x.n * y.d + y.n * x.d;
  int d = x.d * y.d;
  rational z = setr(n, d);
  z = yakubu(z);
  return z;
}

rational divr(rational x, rational y) {
  rational z;

  int n = x.n * y.d;
  int d = x.d * y.n;

  if (d == 0) {
    fprintf(stderr, "Division by zero.\n");
    exit(1);
  }

  z = setr(n, d);
  z = yakubu(z);
  return z;
}

rational subr(rational x, rational y)
{
  rational z;

  int n = x.n * y.d - y.n * x.d;
  int d = x.d * y.d;
  z = setr(n, d);
  z = yakubu(z);
  return z;
}

void example5(void)
{
  rational x;
  x = setr(6, 8);
  printr(x);
}

void check4(int argc, char *argv[])
{
  rational x, y;
  {
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int c = atoi(argv[3]);
    int d = atoi(argv[4]);
    x = setr(a, b);
    y = setr(c, d);
  }
  {
    // addr
    rational z = addr(x, y);
    printr(z);
  }
  {
    // subr
    rational z = subr(x, y);
    printr(z);
  }
  {
    // mulr
    rational z = mulr(x, y);
    printr(z);
  }
  {
    // divr
    rational z = divr(x, y);
    printr(z);
  }
}

int main(int argc, char *argv[])
{
  // example5();
  check4(argc, argv);
  return 0;
}
