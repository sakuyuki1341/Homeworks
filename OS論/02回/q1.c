#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define BSIZE 16
main()
{
        int n;
        char buf[BSIZE];
        n = read(0,buf,BSIZE);
        write(1,buf,n);
        return 0;
}
