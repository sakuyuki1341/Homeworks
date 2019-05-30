#include <stdio.h>
#include <math.h>

int main(void) {
  double x1, x2, y1, y2, ret, xx, yy;
  scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
  xx = (x1 - x2)*(x1 - x2);
  yy = (y1 - y2)*(y1 - y2);
  ret = sqrt(xx + yy);
  printf("%.3f\n", ret);
  return 0;
}
