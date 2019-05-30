// prime.c --- see if an integer is a prime.
#include <stdio.h>
#include <math.h>      // sqrtを使う場合必要
#include <stdbool.h>   // true, false, boolを使う場合必要
bool isprime(int n) {
  int limit = (int)sqrt(n);
  for(int i = 2; i <= limit; ++i) {
    if(n % i == 0) { return false; }
  }
  return true;
}
int main(void) {
  int n;
  printf("n> "); scanf("%d", &n);
  if(isprime(n)) { printf("%d is a prime.\n", n); }
  else           { printf("%d is not a prime.\n", n); }
  return 0;
}
