#include <math.h>
#include <stdio.h>

//#define TEST
#define ENSHU_A
//#define ENSHU_D

void dswap(double *x, double *y) {
  double z = *x; *x = *y; *y = z;
}

void rotate3(double *a, double *b, double *c) {
  double x = *a;
  *a = *c; *c = *b; *b = x;
}

/*
void topolar(double x, double y, double *rad, double *theta) {
  *theta = atan2(x, y);
  *rad = sqrt(x*x + y*y);
}
*/

void divide(int a, int b, int *q, int *r) {
  *q = a / b;
  *r = a - b * (*q);
}

void expect_double(double a, double b, double d, char *msg) {
  printf("%s %.10g:%.10g %s\n", (fabs(a-b)<d)?"OK":"NG" , a, b, msg);
}

void expect_int(int a, int b, char *msg) {
  printf("%s %d:%d %s\n", (a-b)?"NG":"OK" , a, b, msg);
}

int main(void) {
#ifdef TEST
  double a = 3.14, b = 2.71; dswap(&a, &b);
  expect_double(a, 2.71, 1e-10, "a should be 2.71");
  expect_double(b, 3.14, 1e-10, "b should be 3.14");
#endif
#ifdef ENSHU_A
  double a = 3.14, b = 2.71, c = 1.41; rotate3(&a, &b, &c);
  expect_double(a, 1.41, 1e-10, "a should be 1.41");
  expect_double(b, 3.14, 1e-10, "b should be 3.14");
  expect_double(c, 2.71, 1e-10, "c should be 2.71");
#endif
#ifdef ENSHU_D
  int a = 13, b = 3;
  int q, r; divide(a, b, &q, &r);
  expect_int(q, 4, "q should be 4");
  expect_int(r, 1, "r should be 1");
#endif

}
