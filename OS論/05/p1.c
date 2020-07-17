#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

main() {
    printf("before fork(): getpid() = %d\n", getpid());
    sleep(3);

    fork();

    printf("after fork(): getpid() = %d\n", getpid());
    sleep(3);

    exit(0);
}
