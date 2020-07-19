#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
main()
{
        int a;
        int *p;
        p = &a;
        a = 0x1234;
        printf("a = %x, *p = %x\n",a,*p);
        *p = 0x5678;
        printf("a = %x, *p = %x\n",a,*p);
        return 0;
}
