#include <stdio.h>
#include <stdlib.h>

void show_byte(unsigned char x) {
    for(int i = 7; i >= 0; i--) {
        printf("%d", (x>>i) & 1);
    }
    printf("\n");
}

int main(void) {
    show_byte((0x6a)&(0xF0));
    return 0;
}
