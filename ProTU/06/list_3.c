#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#define FACT
//#define MUL
#define POWX
//#define EXPOWX

int fact(int n) {
    if(n < 1) {
        return 1;
    } else {
        return n * fact(n-1);
    }
}

int fact1(int n, int r) {
    if(n < 1) {
        return r;
    } else {
        return fact1(n-1, r*n);
    }
}

int fact_1(int n) { return fact1(n, 1); }

int mul(int a, int b) {
    if(b == 0) {
        return 0;
    } else {
        return a + mul(a, b-1);
    }
}

int mul1(int a, int b, int r) {
    if(b == 0) {
        return r;
    } else {
        return mul1(a, b-1, r+a);
    }
}

int mul_1(int a, int b) { return mul1(a, b, 0); }

int mul2(int a, int b, int r) {
    while(true) {
        if(b == 0) {
            return r;
        } else {
            b -= 1;
            r += a;
        }
    }
}

int mul_2(int a, int b) { return mul2(a, b, 0); }

int powx(double x, int n) {
    if(n < 1) {
        return 1.0;
    } else {
        return x * powx(x, n-1);
    }
}

int powx1(double x, int n, double r) {
    if(n < 1) {
        return r;
    } else {
        return powx1(x, n-1, r*x);
    }
}

int powx_1(double x, int n) { return powx1(x, n, 1.0); }

int powx2(double x, int n, double r) {
    while(true) {
        if(n < 1) {
            return r;
        } else {
            n--;
            r *= x;
        }
    }
}

int powx_2(double x, int n) { return powx2(x, n, 1.0); }

double expowx(double x, int n) {
    if(n < 1) {
        return 1.0;
    } else if(n % 2 == 1) {
        return x * expowx(x, n-1);
    } else {
        double y = expowx(x, n/2);
        return y*y;
    }
}

double expowx1(double x, int n, double r) {
    if(n < 1) {
        return r;
    } else if(n % 2 == 1) {
        return expowx1(x, n-1, r*x);
    } else {
        return expowx1(x*x, n/2, r);
    }
}

double expowx_1(double x, int n) { return expowx1(x, n, 1.0); }

double expowx2(double x, int n, double r) {
    while(true) {
        if(n < 1) {
            return r;
        } else if(n % 2 == 1) {
            n--;
            r *= x;
        } else {
            n /= 2;
            x *= x;
        }
    }
}

double expowx_2(double x, int n) { return expowx2(x, n, 1.0); }

//========================================================================
int main(int argv, char *args[]) {
#ifdef FACT
    int n = atoi(args[1]);
    printf("再帰で記述: %d\n末尾再帰で記述: %d\n", fact(n), fact_1(n));
#endif
#ifdef MUL
    int a = atoi(args[1]), b = atoi(args[2]);
    printf("再帰で記述: %d\n末尾再帰で記述: %d\nループで記述: %d\n", mul(a, b), mul_1(a, b), mul_2(a, b));
#endif
#ifdef POWX
    double x = atof(args[1]);
    int n = atoi(args[2]);
    printf("再帰で記述: %d\n末尾再帰で記述: %d\nループで記述: %d\n", powx(x, n), powx_1(x, n), powx_2(x, n));
#endif
#ifdef EXPOWX
    double x = atof(args[1]);
    int n = atoi(args[2]);
    printf("再帰で記述: %f\n末尾再帰で記述: %f\nループで記述: %f\n", expowx(x, n), expowx_1(x, n), expowx_2(x, n));
#endif
//    printf("%", expowx())
    return 0;
}

