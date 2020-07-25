#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void ringring(int sig) {
	printf("process[%d]: signal(%d) received\n",getpid(),sig);
}

main() {
	signal(SIGINT,ringring);
	signal(SIGTERM,ringring);
	signal(SIGKILL,ringring);

	for(;;);

	/* NOT REACHED */
}