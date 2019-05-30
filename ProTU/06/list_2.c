#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//#define GCD
//#define ISEVEN
//#define SUM
#define STRTRIANGLE

int gcd(int x, int y) {
  if(x == y) {
    return x;
  } else if(x > y) {
    return gcd(x-y, y);
  } else {
    return gcd(x, y-x);
  }
}

int gcd2(int x, int y) {
  while(true) {
    if(x == y) {
      return x;
    } else if(x > y) {
      x = x - y;
    } else {
      y = y - x;
    }
  }
}

bool iseven(int n) {
  if(n == 0) {
    return true;
  } else if(n == 1) {
    return false;
  } else {
    return iseven(n - 2);
  }
}

bool iseven2(int n) {
	while(true) {
		if(n == 0) {
			return true;
		} else if(n == 1) {
			return false;
		} else {
			n -= 2;
		}
	}
}

int sum(int a, int b) {
    if(a == 0) {
        return b;
    } else {
        return sum(a-1, b+1);
    }
}

int sum2(int a, int b) {
    while(true) {
        if(a == 0) {
            return b;
        } else {
            a--;
            b++;
        }
    }
}

void strtriangle(char* s) {
    printf("%s\n", s);
    if(*s == '\0') {
        // do nothing
    } else {
        strtriangle(s+1);
    }
}

void strtriangle2(char* s) {
    while(true) {
        printf("%s\n", s);
        if(*s == '\0') {
            break;
        } else {
            s++;
        }
    }
}

int main(int argv, char *args[]) {
#ifdef GCD
	int x = atoi(args[1]), y = atoi(args[2]);
	printf("再帰で記述: %d\nループで記述: %d\n", gcd(x, y), gcd2(x, y));
#endif
#ifdef ISEVEN
	int n = atoi(args[1]);
    printf("再帰で記述: %s\nループで記述: %s\n", iseven(n)?"true":"false", iseven2(n)?"true":"false");
#endif
#ifdef SUM
	int a = atoi(args[1]), b = atoi(args[2]);
    printf("再帰で記述: %d\nループで記述: %d\n", sum(a, b), sum2(a, b));
#endif
#ifdef STRTRIANGLE
    char* s = args[1];
    printf("再帰で記述: \n");
    strtriangle(s);
    printf("ループで記述: \n");
    strtriangle2(s);
#endif
	return 0;
}
