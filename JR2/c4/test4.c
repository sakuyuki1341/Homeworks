#include<stdio.h>

int calc1 (int a) {
        int factorial = 1;
        int i;
        for (i = a; i > 0; i--) {
                factorial *= i;
        }
        return factorial;
}
int calc2 (int a) {
        int sum = 0;
        int i;
        for (i = 1; i <= a; i++) {
                sum += i;
        }
        return sum;
}
int func(int a){
        if(a % 2 == 0){
                return calc1(a);
        } else {
                return calc2(a);
        }
}
int main(void){
        int hoge[8] = {1, 4, 1, 4, 2, 1, 3, 5};
        int sum = 0;
        int i;
        for (i = 0; i < 8; i++) {
                sum += func(hoge[i]);
        }
        printf("%d\n", sum);
        return 0;
}
