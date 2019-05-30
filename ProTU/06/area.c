#include <stdio.h>
//#define DELTA 0.001
#define DELTA 0.00001

#define CIRCLE
#define TRIANGLE 
//#define BALL

int inside_circle(double x, double y) {
  return x*x+y*y <= 4.0;
}

int inside_triangle(double x, double y) {
	return x+y <= 2.0;
}

int inside_ball(double x, double y, double z) {
	return x*x+y*y+z*z <= 4.0;
}

double area(double x1, double x2, double y1, double y2,
            int (*f)(double,double)) {
 int b1 = (*f)(x1,y1), b2 = (*f)(x1,y2);
 int b3 = (*f)(x2,y1), b4 = (*f)(x2,y2), bn = b1+b2+b3+b4;
 if(x2-x1 < DELTA || bn == 0 || bn == 4) {
   return bn*0.25*(x2-x1)*(y2-y1);
 } else {
   double x3 = 0.5*(x1+x2), y3 = 0.5*(y1+y2);
   return area(x1, x3, y1, y3, f) + area(x1, x3, y3, y2, f) +
          area(x3, x2, y1, y3, f) + area(x3, x2, y3, y2, f);
  }
}
/*
double area_3d(double x1, double x2, double y1, double y2, double z1, double z2,
               int (*f)(double,double,double)) {
	int b1 = (*f)(x1,y1,z1), b2 = (*f)(x1,y1,z2); b3 = (*f)(x1,y2,z1);
	int b4 = (*f)(x1,y2,z2), b5 = (*f)(x2,y1,z1); b6 = (*f)(x2,y1,z2);
	int b7 = (*f)(x2,y2,z1), b8 = (*f)(x2,y2,z2); bn = b1+b2+b3+b4+b5+b6+b7+b8;
	if(x2-x1 < DELTA || bn == 0 || bn == 4) {
		return bn*0.25*(x2-x1)*(y2-y1)*(z2-z1);
	} else {
		double x3 = 0.5*(x1+x2), y3 = 0.5*(y1+y2), z3 = 0.5*(z1+z2);
		return area_3d(x1, x3, y1, y3, z1, z3, f) + area_3d(x1, x3, y1, y3, z3, z2, f) +
	*/				 

int main(void) {
#ifdef CIRCLE
  printf("%8.6f\n", area(0, 2, 0, 2, inside_circle));
#endif
#ifdef TRIANGLE
	printf("%8.6f\n", area(0, 2, 0, 2, inside_triangle));
#endif
  return 0;
}
