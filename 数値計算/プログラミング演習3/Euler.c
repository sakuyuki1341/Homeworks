#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//y0:初期条件　x0,xn:区間[x0,tn], n:分割数
double eulerMethod(double y0, double x0, double xn, int n) {
	int i;
	double y, y_correct, x, h;
	y = y0;
	x = x0;
	h = (xn - x0) / n;

	for(i = 1; i <= n; i++) {
		y += y * h;
		x = x0 + i*h;
		y_correct = exp(x);
		printf("x = %f // y = %f // y_correct = %f\n", x, y, y_correct);
	}
	
	return y;
}

int main(void) {
	eulerMethod(1, 0, 1, 20);
	return 0;
}