//
// The Gauss elimination method 
// for solving a system of linear equations 
//     Ax = b
//
#include <stdio.h>
#include <math.h>
#define NMAT 11
//
// solve Ax = b by the Gauss elimination
// 
void gauss_elimination(int nmat, double a[NMAT+1][NMAT+1], double b[NMAT+1], 
		       double x[NMAT+1])	
{
  double m[NMAT+1][NMAT+1];
  int i, j, k;
  //
  // Gauss elimination
  //
  for (k=1; k<nmat; ++k)
    {
      for (i=k+1; i<=nmat; ++i)
	{
	  m[i][k] = a[i][k] / a[k][k];
	  for (j=k+1; j<=nmat; ++j)
	    a[i][j] -= m[i][k] * a[k][j];
	  b[i] -= m[i][k] * b[k];
	} 
    }	
  // 
  // get the solution x by the backward substitution
  //
  for (i=nmat; i>=1; --i)
    {
      x[i] = b[i];
      for (j=nmat; j>=i+1; --j)
	x[i] -= a[i][j] * x[j];
      x[i] /= a[i][i];
    }
}
//
// sample data for the Gauss elimination
//
void data_gauss_elimination(int nmat, double a[NMAT+1][NMAT+1], double b[NMAT+1])
{
  int i, j;
  //
  for (i=1; i<=nmat; ++i)
    for (j=1; j<=nmat; ++j)
      a[i][j] = 0.0;
  //
  a[1][1] = 4.0;
  a[1][2] = 1.0;
  for (i=2; i<nmat; ++i) {
    a[i][i] = 4.0;
    a[i][i-1] = a[i][i+1] = 1.0;
  }
  a[nmat][nmat] = 4.0;
  a[nmat][nmat-1] = 1.0;
  //
  for (i=1; i<=nmat; ++i)
    {
      b[i] = 0.0;
      for (j=1; j<=nmat; ++j) b[i] += a[i][j] * (double)j;
    }
}
//
// -------------------------------------------------------
//
main()
{
  int nmat = 10;
  int i;
  double a[NMAT+1][NMAT+1], b[NMAT+1], x[NMAT+1];
  //
  data_gauss_elimination(nmat, a, b);
  gauss_elimination(nmat, a, b, x);
  //
  // print the solution 
  //
  printf("solution x:\n");
  for (i=1; i<=nmat; ++i)
    {
      printf("%12.5e ", x[i]);
      if (i%5==0) printf("\n");
    }	
  printf("\n");
  //
  return 0;
}
