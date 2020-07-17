#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

main() {
    printf("before execl(): getpid() = %d\n", getpid());
    
    execl("/bin/date", "date", NULL);

    printf("after execl(): getpid() = %d\n", getpid());
    exit(0);
}
