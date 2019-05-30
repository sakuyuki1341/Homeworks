#include <stdio.h>
#include <stdlib.h>
void dswap(double *x, double *y) {
  double z = *x; *x = *y; *y = z;
}
int main(int argc, char *argv[]) {
  double a = atof(argv[1]), b = atof(argv[2]);
  printf("a = %g, b = %g\n", a, b);
  dswap(&a, &b);
  printf("a = %g, b = %g\n", a, b);
  return 0;
}
