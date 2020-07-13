#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define BSIZE 512

char buf[BSIZE];

void copyfile(int fOrigin, int fFake) {
	int n = BSIZE;
	while (n != 0) {
		n = read(fOrigin, buf, BSIZE);
		printf("n = %d", n);
		write(1, buf, n);
		printf("#");
	}
}

int main(int argc, char **argv) {
	int fOrigin, fFake;
	if (argc != 3) {
		printf("incorrect argument\n");
		exit(1);
	}

	fFake = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);
	fOrigin = open(argv[1],O_RDONLY|O_CREAT|O_TRUNC,0666);

	if (fOrigin < 0) {
		//error(argv[1]);
		exit(1);
	}
	
	if (fFake < 0) {
		//error(argv[2]);
		exit(1);
	}

	copyfile(fOrigin, fFake);

	close(fOrigin);
	close(fFake);
	exit(0);
}