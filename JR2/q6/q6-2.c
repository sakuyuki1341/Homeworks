#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static void iswap(char** a, int i, int j) {
    char* x = a[i]; a[i] = a[j]; a[j] = x;
}

void sort(int n, char** a) {
    bool done = false;
    while(!done) {
        done = true;
        for(int i = 1; i < n; i++) {
            if(strcmp(a[i-1], a[i]) > 0) {
                iswap(a,i-1,i);
                done = false;
            }
        }
    }
}

int main(int argc,char *argv[]){
	int i;
	int size = argc - 1;

	char** a = (char**)calloc(size, sizeof(char*));

	for(i=1; i<argc; i++) {
		a[i-1] = argv[i];
    }

	sort(size, a);

	for(i=0; i<size; i++) {
		printf("%s\n", a[i]);
    }

	free(a);

	return 0;
}
