#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
main()
{
        char d[4];
        int *p;
        p = (int *)&d[0];
        d[0] = 0x12;
        d[1] = 0x34;
        d[2] = 0x56;
        d[3] = 0x78;
        printf("*p = %x\n",*p);
        *p = 0x1234;
        printf("*p = %x\n",*p);
        return 0;
}
