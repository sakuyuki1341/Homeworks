#include <stdio.h>
#include <setjmp.h>
jmp_buf(env);
void
func(int n,int arg)
{
        printf("func(%d,%d): start\n",n,arg);
        if (n > 0)
                func(n-1,arg);
        else
                longjmp(env,arg);
        printf("func(%d,%d): end\n",n,arg);
}
main(int argc, char **argv)
{
        int arg, val;
        if (argc < 2)
                return 1;
        arg = atoi(argv[1]);
        if ((val = setjmp(env)) == 0)
                func(5,arg);
        printf("val = %d\n",val);
        return 0;
}
