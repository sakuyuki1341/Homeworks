#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
main()
{
        int *p;
        p = (int *)NULL;
        printf("*p = %x\n",*p);
        *p = 0x1234;
        printf("*p = %x\n",*p);
        return 0;
}
