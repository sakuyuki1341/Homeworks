#include <stdio.h>
void
func(int n,int arg)
{
        printf("func(%d,%d): start\n",n,arg);
        if (n > 0)
                func(n-1,arg);
        printf("func(%d,%d): end\n",n,arg);
}
main(int argc, char **argv)
{
        int arg;
        if (argc < 2)
                return 1;
        arg = atoi(argv[1]);
        func(5,arg);
        return 0;
}
