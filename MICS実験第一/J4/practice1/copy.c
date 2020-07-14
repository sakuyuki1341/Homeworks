/*writeとreadを使用したプログラム*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define BSIZE 256

char buf[BSIZE];

void copyfile(int fOrigin, int fFake) {
	int n = BSIZE;
	while (n != 0) {
		n = read(fOrigin, buf, BSIZE);
		write(fFake, buf, n);
	}
}

int main(int argc, char **argv) {
	int fOrigin, fFake;
	if (argc != 3) {
		printf("incorrect argument\n");
		exit(1);
	}

	fOrigin = open(argv[1],O_RDONLY);
	fFake = open(argv[2],O_WRONLY|O_CREAT, 0666);

	if (fOrigin < 0) {
		exit(1);
	}
	
	if (fFake < 0) {
		exit(1);
	}

	copyfile(fOrigin, fFake);

	close(fOrigin);
	close(fFake);
	exit(0);
}
