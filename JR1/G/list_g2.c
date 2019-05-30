#include <stdio.h>

int uniq(int n, int a[]);

int main(void) {
  int n;
  scanf("%d", &n);
  int a[n];
  int i;
  for(i = 0; i < n; i++){
    scanf("%d", a + i);
  }
  printf("%d\n", uniq(n, a));
  return 0;
}

int uniq(int n, int a[]) {
  int i, j;
  int ret = 1;
  for(i = 0; i < n; i++) {
    for(j = i+1; j < n; j++) {
      if(a[i] == a[j]) {
        ret = 0;
      }
    }
  }
  return ret;
}
