#include <stdio.h>
#include <stdlib.h>

main() {
    int i;

    if (fork() == 0) {
        for (i = 0; i < 5; i++) {
            printf("child process: getpid() = %d, getppid() = %d\n", getpid(), getppid());
            sleep(3);
        }
        exit(0);
    }

    sleep(8);

    printf("parent process: getpid() = %d, getppid() = %d\n", getpid(), getppid());

    exit(0);
}
