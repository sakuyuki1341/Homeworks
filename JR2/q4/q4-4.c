#include <stdio.h>
#include <stdlib.h>

int combination(int n, int r){
	if(r == 0 || r == n) {
        return 1;
    } else if(r == 1) {
        return n;
    } else {
        return combination(n-1, r-1) + combination(n-1, r);
    }
}

int main(int argc, char *argv[]){
	printf("%d\n", combination(atoi(argv[1]), atoi(argv[2])));
	return 0;
}
