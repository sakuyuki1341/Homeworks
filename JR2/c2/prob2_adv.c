#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    unsigned int *a;
    *a = 0x3DC80000;
    float* f = (float*)a;
    printf("%.10f\n", &a);
    return 0;
}
