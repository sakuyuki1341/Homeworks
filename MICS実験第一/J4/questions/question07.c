#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

main(int argc, char *argv[]) {
    char *cmd[argc-1];

    int i;
    for(i = 0; i < argc-2; i++) {
        cmd[i] = argv[i+1];
    }
    cmd[argc-2] = NULL;

    char *file;
    file = argv[argc-1];

    int fd;

    if ((fd = open(file, O_WRONLY|O_CREAT|O_TRUNC,0644)) < 0) {
        perror(file);
        exit(1);
    }

    close(1);
    dup(fd);
    close(fd);
    
    execvp(cmd[0], cmd);
}
