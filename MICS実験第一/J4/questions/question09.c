/* sample10.c */
#include <stdio.h>
#include <stdlib.h>
main(int argc, char **argv) {
    int pid, i;
    for(i = argc; i > 0; --i) {
        if ((pid = fork()) == 0) {
            /* child process */
            printf("%s\n",*(argv + i));
            exit(0);
        }
        /* parent process */
        if (pid == -1) {
            perror("fork");
            exit(1);
        }
    }
    for(i = argc; i > 0; --i) {
        if (wait(NULL) == -1) {
            perror("wait");
            exit(1);
        }
    }
    exit(0);
}
