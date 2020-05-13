#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//y0:初期条件　x0,xn:区間[x0,tn], n:分割数
double runge_kuttaMethod(double y0, double x0, double xn, int n) {
	int i;
	double y, y_correct, x, h, k1, k2, k3, k4;
	y = y0;
	x = x0;
	h = (xn - x0) / n;

	for(i = 1; i <= n; i++) {
		k1 = y * h;
		k2 = (y + k1 / 2) * h;
		k3 = (y + k2 / 2) * h;
		k4 = (y + k3) * h;
		y += (k1 + 2*k2 + 2*k3 + k4) / 6;
		x = x0 + i*h;
		y_correct = exp(x);
		printf("x = %f // y = %f // y_correct = %f\n", x, y, y_correct);
	}
	
	return y;
}

int main(void) {
	runge_kuttaMethod(1, 0, 1, 20);
	return 0;
}
