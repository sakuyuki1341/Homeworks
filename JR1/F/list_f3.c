#include <stdio.h>

int main(void) {
  int toshi;
  scanf("%d", &toshi);
  if(toshi % 4 == 0) {
    if(toshi % 100 == 0 && toshi % 400 != 0) {
      printf("NO\n");
    } else {
      printf("YES\n");
    }
  } else {
    printf("NO\n");
  }
  return 0;
}
