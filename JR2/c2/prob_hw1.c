#include <stdio.h>

int main(void) {
    float a, b, c, d, s;
    a =  100001.0;
    b =  0.123456;
    c =  0.111111;
    d = -100000.0;
    s = 0.0;
    s += a;
    s += d;
    s += b;
    s += c;
    printf("%f\n", s);
}
