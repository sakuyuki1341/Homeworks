#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BSIZE 1024

int main(int argc, char **argv) {
	int outFile, pid, p_fd[2];
	char *new_program, **new_argv, buf[BSIZE];
	if (argc < 2) {
		fprintf("incorrect argument\n");
		exit(1);
	}
	outFile = open(argv[1],O_WRONLY|O_CREAT, 0666);
	pipe(p_fd);

	if ((pid = fork()) == 0) {
		/* child process */
		close(p_fd[0]);
		close(1);
		dup(p_fd[1]);
		close(p_fd[1]);
		new_program = argv[2];
		new_argv = &argv[2];
		execvp(new_program,new_argv);
		perror(new_program);
		exit(1);
	}

	/* parent process */
	if (pid == -1) {
		perror("fork");
		exit(1);
	}

	int n = BSIZE;
	while (n != 0) {
		n = read(p_fd[0], buf, BSIZE);
		write(outFile, buf, n);
		printf("%s", buf);
	}
}