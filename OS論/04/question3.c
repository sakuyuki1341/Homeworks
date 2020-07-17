#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
main()
{
        printf("getpid() = %d\n",getpid());
        printf("getppid() = %d\n",getppid());
        return 0;
}
