#include <stdio.h>

int main(void) {
    int a[100];
    int i = 1;
    int flag2 = 1;
    while(1){
        printf("> ");
        scanf("%d", &a[i]);
        for(int j = 0; j < i; j++) {
            if(a[i] == 0) {
                return 0;
            }
            if(a[i] == a[j]) {
                printf("%d\n", j);
                flag2 = 0;
                i--;
            }
        }
        if(flag2) {
            printf("%d\n", i);
        }
        i++;
        flag2 = 1;
    }
    return 0;
}
