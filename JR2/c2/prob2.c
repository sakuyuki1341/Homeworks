#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main(int ac, char *av[]) {
// ここから(-1)^0 * 1.1001 * 2^-4の計算
    int a[] = {1,0,0,1};
    float f = 1;
    for(int i = 0; i < 4; i++) {
        if(a[i] == 1) {
            float temp = 1;
            for(int j = 0; j < i+1; j++) {
                temp /= 2;
            }
            f += temp;
        }
    }
    for(int i = 0; i < 4; i++) {
        f /= 2;
    }
    printf("%.10f\n", f);

// --------------------------------------------------------
// ここから(-1)^0 * 1.10011001 * 2^-4の計算
    int b[] = {1,0,0,1,1,0,0,1};
    double d = 1;
    for(int i = 0; i < 8; i++) {
        if(b[i] == 1) {
            double temp = 1;
            for(int j = 0; j < i+1; j++) {
                temp /= 2;
            }
            d += temp;
        }
    }
    for(int i = 0; i < 8; i++) {
        d /= 2;
    }
    printf("%.10lf\n", d);
    return 0;
}
