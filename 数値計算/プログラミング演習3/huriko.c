#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func(double x, double t) {
	double upper = 1 - cos(x);
	double under = 1 + cos(x);
	return 2 * t * log(upper / under);
}

//x0:初期条件　t0,tn:区間[t0,tn], n:分割数
double runge_kuttaMethod(double x0, double t0, double tn, int n) {
	int i;
	double x, t, h, k1, k2, k3, k4;
	x = x0;
	t = t0;
	h = (tn - t0) / n;

	for(i = 1; i <= n; i++) {
		k1 = h * func(x, t);
		k2 = h * func(x + k1/2, t + h/2);
		k3 = h * func(x + k2/2, t + h/2);
		k4 = h * func(x + k3, t + h);
		x += (k1 + 2*k2 + 2*k3 + k4) / 6;
		t = t0 + i*h;
		printf("t = %f // x = %f \n", t, x);
	}
	
	return x;
}

int main(void) {
	runge_kuttaMethod(1, 0, 1, 20);
	return 0;
}
