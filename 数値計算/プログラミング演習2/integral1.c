#include <stdio.h>
#include <math.h>
//
// numerical integration of the function "func(x)" over an interval [xmin, xmax]
// by the trapezoidal rule
//
// (usage)
// func : the integrand function
// [xmin, xmax] : the interval of the integral
// nint : the number of sampling points
//
double trape_rule(double (*func)(double), double xmin, double xmax, int nint) {
	double h; // mesh size
	double s; // numerical value of the integral
	double x;
	int n;
	//
	h = (xmax - xmin) / nint;
	s = 0.5 * (func(xmin) + func(xmax));
	for (n=1; n<=nint-1; ++n) {
		x = xmin + n * h;
		s += func(x);
	}
	s *= h;
	return s;
}
//
double func(double x) {
	return 1.0 / (1.0 + x*x);
}
//
int main() {
	double s, se, error, xmin, xmax;
	int n, nmin, nmax;
	//
	xmin = -1.0;
	xmax = 1.0;
	se = 0.5 * M_PI;
	printf("# S(exact) = %22.15e\n", se);
	printf("# N      S(numerical)    relative error\n");
	printf("#--------------------------------------\n");
	//
	nmin = 8;
	nmax = 256;
	for (n=nmin; n<=nmax; n+=8) {
		s = trape_rule(func, xmin, xmax, n);
		error = fabs(s - se) / fabs(se);
		printf("%3d %22.15e %10.3e\n", n, s, error);
//		printf("%3d %10.3e\n", n, error);
//		printf("%3d %22.15e\n", n, s);
	}
	//
	return 0;
}
