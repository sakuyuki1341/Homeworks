#include <stdio.h>
#include "eps.h"

void a_1(void);
void a_2(void);

int main(void) {

  a_1();
  a_2();

  eps_close();
  return 0;
}

void a_1(void) {
  eps_open("a_1.ps", 480, 480);
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      eps_drawrect(j*100 + 40, i*100 + 40, 60, 60);
    }
  }
}

void a_2(void) {
  eps_open("out.ps", 600, 600);
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; i++) {
      if((i+j)%2 == 0) {
	eps_fillrect(j*100, i*100, 100, 100);
      }
    }
  }
}
