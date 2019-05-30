#include <stdio.h>

int duplicatek(int n, int k, int a[]);

int main(void) {
  int n, k, i;
  scanf("%d %d", &n, &k);
  int a[n];
  for(i = 0; i < n; i++) {
    scanf("%d", a + i);
  }
  printf("%d\n", duplicatek(n, k, a));
  return 0;
}

int duplicatek(int n, int k, int a[]) {
  int ret = 0;
  int h[201] = {};
  int i;
  for(i = 0; i < n; i++) {
    h[a[i] + 100]++;
  }
  for(i = 0; i < 201; i++) {
    if(h[i] >= k) {
      ret = 1;
    }
  }
  return ret;
}
