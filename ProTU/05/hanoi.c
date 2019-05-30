#include <stdio.h>
#include <stdlib.h>

void hanoi(int k, int x, int y, int z) {
  if(k == 1) {
    printf("move disc %d from %c to %c.\n", k, x, y);
  } else {
    hanoi(k-1, x, z, y);
    printf("move disc %d from %c to %c.\n", k, x, y);
    hanoi(k-1, z, y, x);
  }
}
int main(int argc, char *argv[]) {
  hanoi(atoi(argv[1]), 'A', 'B', 'C'); return 0;
}
