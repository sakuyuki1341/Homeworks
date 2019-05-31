#include<stdio.h>
#include <stdlib.h>

void func(int no){
	if (no >= 1){
		func(no-1);
		printf("%d ", no);
	}
}
int main(int argc, char *argv[])
{
	func(atoi(argv[1]));
	printf("\n");
	return 0;
}

