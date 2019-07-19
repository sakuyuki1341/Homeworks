#include <stdio.h>
#include <math.h>
#include <stdbool.h>

void syahen(double a, double b);
void njou(int n);
void soinsuu(int n);
bool isprime(int n);
void prime_number(int n);
void fibonacci(int n);

int main (void){
  /*
  int a; printf("a> "); scanf("%d\n", &a);
  int b; printf("b> "); scanf("%d\n", &b);
  syahen(a,b);
  */

  int n; printf("n> "); scanf("%d", &n);
  //njou(n);
  //soinsuu(n);
  //prime_number(n);
  fibonacci(n);
  return 0;
}

void syahen(double a, double b) {
  printf("%lf\n", sqrt(a*a + b*b));
}

void njou(int n) {
  int ret = 2;
  double re = 1;
  if(n == 0) {
    printf("1");
  } else if(n > 0) {
    for(n; n > 1; n--) {
      ret = ret * 2;
    }
    printf("%d\n", ret);
  } else {
    for(n; n < 0; n++) {
      re = re / 2;
    }
    printf("%g\n", re);
  }
}

void soinsuu(int n) {
  int i = 2;
  while(n >= i) {
    if(n % i != 0) {
      i++;
    } else {
      n /= i;
      printf("%d ", i);
    }
  }
  printf("\n");
}

bool isprime (int n) {
  int limit = (int)sqrt(n);
  for(int i = 2; i <= limit; i++) {
    if(n % i == 0) {
      return false;
    }
  }
  return true;
}

void prime_number(int n){
  int limit = (int)sqrt(n);
  for(int i = 2; i <= limit; i++) {
    if(n % i == 0) {
      printf("%d\n", i);
    }
  }
}

/*==================================================*
  引数nを与えられると、第n項までのフィボナッチ数列を表示してく
  れる関数
  戻り値はない
 *==================================================*/
void fibonacci(int n) {
  int a, b, x;
  a = b = x = 1;
  printf("1 ");
  for(int i = 1; i < n; i++) {
    x = b;
    b = b + a;
    a = x;
    printf("%d ", a);
  }
}
