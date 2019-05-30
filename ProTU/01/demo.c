// eps_demo.c --- demonstration of eps library.
#include <stdio.h>
#include "eps.h"

int main(void) {
  eps_open("out.ps", 480, 480);   
  eps_cmd("240 240 translate");   
  eps_drawline(-200, 0, 200, 0);  
  eps_drawline(0, 200, 0, -200);  
  for(int i = 1; i <= 8; ++i) {
    eps_num(i*0.1); eps_cmd("setgray");
    eps_cmd("4 setlinewidth");         
    eps_drawrect(i*20, i*20, 30, 30);  
    eps_num(i*0.1); eps_cmd("1.0 1.0 sethsbcolor");
    eps_fillcircle(-i*20, -i*20, 15);   
  }
  int f1 = eps_newfont("Courier", 20);      
  eps_puts(f1, -180, 50, "This is a pen."); 
  int f2 = eps_newfont("Helvetica", 30);    
  eps_puts(f2, 20, -50, "How are you?");    
  eps_close();                          
  return 0;
}
