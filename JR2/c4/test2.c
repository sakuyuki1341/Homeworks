#include <stdio.h>
void func (int a) {
    printf("%d\n", a);
}
int main(void){
    int hoge[8] = {1, 4, 1, 4, 2, 1, 3, 5};
    int i;
    for (i = 0; i < 8; i++) {
        func(hoge[i]);
    }
    return 0;
}
