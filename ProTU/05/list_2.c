#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 256

void one_two_dec(int n, int *arr, int now) {
  if(n == 1) {
    for(int i = 0; i < now; i++) {
      printf("%d", arr[i]);
    }
    printf("1\n");
  } else if(n > 1){
    //int arr_now[ARR_SIZE];
    //for(int i = 0; i < now; i++) {
    //  arr_now[i] = arr[i];
    //}
    arr[now] = n;
    now++;
    one_two_dec(n-1, arr, now);
    one_two_dec(n-2, arr, now);
 }
}

int main(int argc, char *argv[]) {
  int arr[ARR_SIZE];
  int now = 0;
  one_two_dec(atoi(argv[1]), arr, now);
  return 0;
}
