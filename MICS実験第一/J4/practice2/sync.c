#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int remcmd = argc-1;
	int pid, w;
	int i;
	for (i = 0; i < remcmd; i++) {
		switch (pid = fork()) {
		case 0:
			/* child process */
			char *arg = argv[i+1];
			execl("/usr/bin/ping", "ping", arg, NULL);
			exit(1);
		case -1:
			perror("fork");
		default:
			/* parent process */
			break;
		}
	}
	if((w = wait(NULL)) == -1) {
		perror("wait");
		exit(1);
	}
	printf("/usr/bin/ping: done\n");
	exit(0);
}