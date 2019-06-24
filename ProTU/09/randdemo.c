// randdemo.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define ENSHU_EX
#define ENSHU_1

int main(int argc, char *argv[]) {
#ifdef ENSHU_EX
    int i, n = atoi(argv[1]);
    srand(time(NULL));
    for(i = 0; i < n; ++i) { printf(" %d", rand() % 1000); }
    printf("\n");
    for(i = 0; i < n; ++i) { printf(" %.3f", rand()/(double)RAND_MAX); }
    printf("\n");
#endif

#ifdef ENSHU_1
    int p[6] = {0};
    for(int i = 0; i < 6000; i++) {
        p[rand() % 6]++;
    }
    for(int i = 0; i < 6; i++) {
        printf("%d: %d times\n", i+1, p[i]);
    }
#endif
  return 0;
}
