#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

main(int argc, char **argv) {
    int val, w, status;

    if (argc == 1) {
        fprintf(stderr, "usage: %s number\n", argv[0]);
        exit(1);
    }

    if(fork() == 0) {
        val = atoi(argv[1]);
        printf("child proces: getpid = %d, val = %d\n", getpid(), val);
        exit(val);
    }

    w = wait(&status);

    printf("parent proces: w = %d, status = %d\n", w, status);

    exit(0);
}
