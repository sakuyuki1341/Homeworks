#include <stdio.h>

int main(void) {
    double i = 2, j = 3;
    double x = i / j + j / i;
    printf("%.10lf\n", x);
    return 0;
}
