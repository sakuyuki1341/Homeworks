#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define N 32768
char a[N][N];
char b[N][N];
main()
{
        clock_t start, end;
        start = clock();
        int i, j;
        for (j = 0; j < N; j++)
                for (i = 0; i < N; i++)
                        b[i][j] = a[i][j];
        end = clock();
        printf("time = %.2f\n",(double)(end-start)/CLOCKS_PER_SEC);
        return 0;
}
