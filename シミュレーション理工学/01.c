#include <stdio.h>
#include <math.h>

void initial(double *n, double *m, double *k, double *dt) {
	*n = 1;
	*m = 0;
	*k = 0;
	*dt = 1;
	return;
}

void euler(double *n, double *m, double *k, double dt) {
	double tmp1, tmp2;

	tmp1 = log(2) * *n * (dt / 14.8);
	tmp2 = log(2) * *m * (dt / 16.1);
	*n += -tmp1;
	*m += -tmp2 + tmp1;
	*k += tmp2;
	return;
}

void main() {
	int i, imax;
	double n, m, k, dt;

	initial(&n, &m, &k, &dt);
	i = 0;
	imax = 160;
	
	FILE *fp;
	fp = fopen("result.plt", "w");
	fprintf(fp, "%4d%6.3f%6.3f%6.3f\n",i, n, m, k);
	while (i <= imax) {
		euler(&n, &m, &k, dt);
		i++;
		fprintf(fp, "%4d%6.3f%6.3f%6.3f\n",i, n, m, k);
	}
}