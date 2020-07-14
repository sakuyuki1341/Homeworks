#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define BSIZE 1024

int main(int argc, char **argv) {
	int w, outFile, pid, p_fd[2];
	char *new_program, **new_argv, buf[BSIZE];
	if (argc < 2) {
		printf("incorrect argument\n");
		exit(1);
	}
	outFile = open(argv[1],O_WRONLY|O_CREAT, 0666);
	pipe(p_fd);

	if ((pid = fork()) == 0) {
		/* child process */
		int n = BSIZE;
		while (n > 0) {
			n = read(0, buf, BSIZE);
			write(outFile, buf, n);
			write(p_fd[1], buf, n);
		}
		exit(1);
	}

	/* parent process */
	if (pid == -1) {
		perror("fork");
		exit(1);
	}

	if((w = wait(NULL)) == -1) {
		perror("wait");
		exit(1);
	}

	close(p_fd[1]);
	close(0);
	dup(p_fd[0]);
	close(p_fd[0]);

	new_program = argv[2];
	new_argv = &argv[2];
	execvp(new_program, new_argv);
	exit(1);
}