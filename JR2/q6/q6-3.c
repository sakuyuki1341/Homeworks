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

void recursive_sort(char** a, int i, int j) {
    if(j <= i) {
        return;
    }
    int s = i;
    char* pivot = a[j];
    for(int k = i; k < j; ++k) {
        if(strcmp(a[k], pivot) < 0) {
            iswap(a, s++, k);
        }
    }
    iswap(a, j, s); recursive_sort(a, i, s-1); recursive_sort(a, s+1, j);
}

int main(int argc,char *argv[]){
	int i;
	int size = argc - 1;

	char** a = (char**)calloc(size, sizeof(char*));

	for(i=1; i<argc; i++) {
		a[i-1] = argv[i];
    }

	recursive_sort(a, 0, size-1);

	for(i=0; i<size; i++) {
		printf("%s\n", a[i]);
    }

	free(a);

	return 0;
}
