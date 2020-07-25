#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void ringring(int sig) {
	printf("process[%d]: signal(%d) received\n", getpid(), sig);
	exit(0);
}

main() {
	signal(SIGALRM, ringring);
	alarm(10);

	for (;;);

	/* NOT REACHED */
}