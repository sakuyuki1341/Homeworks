#include <stdio.h>
#include <stdbool.h>
#include "iqueue.h"

int main(void) {
    iqueuep k = iqueue_new(100);
    iqueuep g = iqueue_new(100);
    int a;
    while(1){
        printf("> ");
        scanf("%d", &a);
        if(a == 0) {
            break;
        } else if(a % 2 == 0) {
            iqueue_enq(g, a);
        } else {
            iqueue_enq(k, a);
        }
    }
    while(iqueue_isempty(k) == false) {
        a = iqueue_deq(k);
        printf("%d ", a);
    }
    while(iqueue_isempty(g) == false) {
        a = iqueue_deq(g);
        printf("%d ", a);
    }
    printf("\n");
    return 0;
}

