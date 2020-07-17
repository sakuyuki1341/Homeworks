#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main() {
    execl("./s2020062302", "s2020062302", "aaaa", "bb", NULL);

    perror("execl");
    exit(0);
}
