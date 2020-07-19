#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define N 32768
char a[N+1][N+1];
char b[N+1][N+1];
main()
{
        int i, j;
        for (j = 0; j < N; j++)
                for (i = 0; i < N; i++)
                        b[i][j] = a[i][j];
        return 0;
}
