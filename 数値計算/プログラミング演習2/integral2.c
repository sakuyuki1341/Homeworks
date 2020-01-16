#include <stdio.h>
#include <math.h>
//
// numerical integration of a function "func(x)' over the infinite interval
// by the trapezoidal rule
// (usage)
// func : the integrand function
// h : the mesh size
// np : the number of sampling points on the positive side
// nm : the number of sampling points on the negative side
//
double trape_rule(double (*func)(double), double h, int *np, int *nm) {
	double s;	// the numerical value of the integral
	double x, term;
	double eps = 1.0e-15;	// if |func(x)| < eps, truncate the infinite sum
	int n, nmax = 100;
	//
	s = func(0.0);
	for (n=1; n<=nmax; ++n) {
		x = n * h;
		term = func(x);
		s += term;
		if (fabs(term) < eps) {
			*np = n;
			break;
		}
	}
	for (n=1; n<=nmax; ++n) {
		x = - n * h;
		term = func(x);
		s += term;
		if (fabs(term) < eps) {
			*nm = n;
			break;
		}
	}
	s *= h;
	return s;
}
//
double func(double x) {
	return exp(-x*x);
}
//
int main() {
	double s;		// the numerical value of the integral
	double se;		// the exact value of the integral
	double error;	// the error of the numerical integral
	double h;		// the mesh size
	int np, nm, n;
	// np : the number of sampling points on the positive side
	// nm : the number of sampling points on the negative side
	// n = np + nm + 1 : the number of sampling points
	int k;
	//
	se = sqrt(M_PI);
	printf("# S(exact) = %22.15e\n", se);
	printf("#    h        N+   N-  N      S(numerical)    relative error\n");
	printf("#-----------------------------------------------------------\n");
	//
	h = 2.0;
	for (k=1; k<=3; ++k) {
		h *= 0.5;
		s = trape_rule(func, h, &np, &nm);
		n = np + nm + 1;
		error = fabs(s - se) / fabs(se);
		printf("%12.5e %3d %3d %3d %22.15e %10.3e\n", h, np, nm, n, s, error);
	}
	//
	return 0;
}
