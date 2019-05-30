#include <stdio.h>

int num_visible_buildings(int n, int h[]);

int main(void) {
  int n, i;
  scanf("%d", &n);
  int h[n];
  for(i = 0; i < n; i++) {
    scanf("%d", h + i);
  }
  int ret = num_visible_buildings(n, h);
  printf("%d\n", ret);
  return 0;
}

int num_visible_buildings(int n, int h[]) {
  int ret, i, j, all;
  ret = 0;
  for(i = 1; i < n; i++) {
    all = 0;
    for(j = 0; j < i; j++) {
      if(h[j] >= h[i]) {
        all++;
      }
    }
    if(all == 0) {
      ret++;
    }
  }
  return ret + 1;
}
