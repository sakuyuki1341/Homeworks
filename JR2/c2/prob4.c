#include <stdio.h>

int main(void) {
    float x, y;
    x = 777777.7;
    y = 1.111111;
    y *= 10;
    x += y;
    printf("%f\n", x);
    return 0;
}
