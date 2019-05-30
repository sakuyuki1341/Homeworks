#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float log_float(float f) {
	int *iPtr;
	int exp;
	float log2 = 0.301, result;
	iPtr = (int*)&f;
	exp = *iPtr >> 23;

	result = (exp - 127) * log2;
	return result;
}

double log_double(double d) {
	long *iPtr;
	long  exp;
	double log2 = 0.301, result;
	iPtr = (long*)&d;
	exp = *iPtr >> 52;

    result = (exp - 1023) * log2;
    return result;
}


int main(int argc, char *argv[]) {
    float  f, f_exp;
    double d, d_exp;

    f = atof(argv[1]);
    d = atof(argv[2]);

    f_exp = log_float(f);
    d_exp = log_double(d);

    printf("%.3f,%.3lf\n", f_exp, d_exp);
    return 0;
}
