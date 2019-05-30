#include <stdio.h>

int nearest_point(int n, double x[], double y[]);

int main(void) {
  int n, i;
  scanf("%d", &n);
  double x[n];
  double y[n];
  for(i = 0; i < n; i++) {
    scanf("%lf", x + i);
  }
  for(i = 0; i < n; i++) {
    scanf("%lf", y + i);
  }
  printf("%d\n", nearest_point(n, x, y));
  return 0;
}

int nearest_point(int n, double x[], double y[]) {
  int ret = 0;
  int i;
  double min = x[0]*x[0] + y[0]*y[0];
  for(i = 0; i < n; i++) {
    if(x[i]*x[i] + y[i]*y[i] <= min) {
      ret = i;
      min = x[i]*x[i] + y[i]*y[i];
    }
  }
  return ret;
}
