#include <stdio.h>
int func (int a) {
        return a*a + 1;
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
