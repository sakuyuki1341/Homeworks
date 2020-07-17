#include <stdio.h>
#include <unistd.h>

main(int argc, char *argv[]) {
    char *cmd[argc];

    int i;
    for(i = 0; i < argc-1; i++) {
        cmd[i] = argv[i+1];
        //printf("%s\n", cmd[i]);
    }
    cmd[argc-1] = NULL;
    
    execvp(cmd[0], cmd);
}
