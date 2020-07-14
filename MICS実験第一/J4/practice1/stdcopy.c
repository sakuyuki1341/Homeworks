/*標準入出力ライブラリを用いたプログラム*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define BSIZE 256

char buf[BSIZE];

void copyfile(FILE *fOrigin, FILE *fFake) {
	while ((fgets(buf, BSIZE, fOrigin)) != NULL) {
		fputs(buf, fFake);
	}
}

int main(int argc, char **argv) {
	FILE *fOrigin, *fFake;
	if (argc != 3) {
		printf("incorrect argument\n");
		exit(1);
	}

	fOrigin = fopen(argv[1],"r");
	fFake = fopen(argv[2],"w");

	if (fOrigin < 0) {
		exit(1);
	}
	
	if (fFake < 0) {
		exit(1);
	}

	copyfile(fOrigin, fFake);

	fclose(fOrigin);
	fclose(fFake);
	exit(0);
}
