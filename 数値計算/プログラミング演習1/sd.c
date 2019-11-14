/*
  solve a linear equation Ax = b
  by the steepest descent method
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NMAX 100
/*
  matrix-vector product Ax
  (input)
  n_mat : dimension
  a_mat : matrix Ax
  x_vec : vector x
  (output)
  ax_vec : vector Ax
 */
void mv_prod(int n_mat, double a_mat[NMAX+1][NMAX+1], double x_vec[NMAX+1], 
	     double ax_vec[NMAX+1])
{
  int i, j;
  double s;
  for (i=1; i<=n_mat; ++i)
    {
      s = 0.0;
      for (j=1; j<=n_mat; ++j) s += a_mat[i][j] * x_vec[j];
      ax_vec[i] = s;
    }
}
/*
  vector-vector product (inner product) (x,y)
  (input)
  n_mat : dimension
  x_vec : vector x
  y_vec : vector y
  (output)
  xy : vector-vector product
 */
void vv_prod(int n_mat, double x_vec[NMAX+1], double y_vec[NMAX+1], 
	     double *xy)
{
  int i;
  double s = 0.0;
  //	
  for (i=1; i<=n_mat; ++i) s += x_vec[i] * y_vec[i];
  *xy = s;
}
/*
  the steepest descent method for a linear equation Ax = b
  (input)
  n_mat : dimension
  a_mat : matrix A
  b_vec : vector b
  (output)
  x_vec : solution x
 */
void sd_method(int n_mat, double a_mat[NMAX+1][NMAX+1], double b_vec[NMAX+1], 
	       double x_vec[NMAX+1])
{
  printf("# steepest descent method\n");
  printf("# k residual\n");
  printf("#-----------\n");
  //
  double p_vec[NMAX+1], r_vec[NMAX+1], ap_vec[NMAX+1], ax_vec[NMAX+1];
  // vector p, r, Ap, Ax0
  double alpha, beta, r2, r2new, pap, r_norm, b_norm, pr;
  // alpha, beta, ||r(old)||^2, ||r(new)||^2, (p, Ap), ||r||, ||b||, (p, r)
  int k_max, l_conv, i, k;
  double s;
  double eps = 1.0e-15; // relative residual tolerance
  //
  vv_prod(n_mat, b_vec, b_vec, &b_norm);
  b_norm = sqrt(b_norm);
  //
  // initial step
  //
  for (i=1; i<=n_mat; ++i) x_vec[i] = 0.0;
  mv_prod(n_mat, a_mat, x_vec, ax_vec);
  for (i=1; i<=n_mat; ++i)
    r_vec[i] = p_vec[i] = b_vec[i] - ax_vec[i];	
  mv_prod(n_mat, a_mat, p_vec, ap_vec);
  vv_prod(n_mat, r_vec, r_vec, &r2new);
  //
  // general step
  //
  k_max = 50;
  l_conv = 0;
  for (k=1; k<=k_max; ++k)
    {
      r2 = r2new;
      vv_prod(n_mat, p_vec, r_vec, &pr);
      vv_prod(n_mat, p_vec, ap_vec, &pap);
      alpha = pr / pap;
      for (i=1; i<=n_mat; ++i) x_vec[i] += alpha * p_vec[i];
      for (i=1; i<=n_mat; ++i) r_vec[i] -= alpha * ap_vec[i];
      vv_prod(n_mat, r_vec, r_vec, &r2new);
      r_norm = sqrt(r2new); 
      printf("%2d %10.3e \n", k, r_norm);
      if (r_norm < eps * b_norm) {
	++l_conv;
	break;
      }
      for (i=1; i<=n_mat; ++i) p_vec[i] = r_vec[i];
      mv_prod(n_mat, a_mat, p_vec, ap_vec);
    }
  if (l_conv == 0) printf("SD method not convergent. \n");
  printf("\n");
}
/*
  give the coefficient matrix and the vector b
  (output)
  n_mat : dimension
  a_mat : matrix A
  b_vec : vector b
 */
void data_sd(int *n_mat, double a_mat[NMAX+1][NMAX+1], double b_vec[NMAX+1])
{
  int i, j, n = 50;
  double s;
  *n_mat = n;
  //
  for (i=1; i<=n; ++i)
    for (j=1; j<=n; ++j)
      a_mat[i][j] = 0.0;
  //
  for (i=1; i<=n; ++i) a_mat[i][i] = 8.0;
  for (i=1; i<=n-1; ++i) a_mat[i][i+1] = 1.0;
  for (i=2; i<=n; ++i) a_mat[i][i-1] = 1.0;
  for (i=1; i<=n-3; ++i) a_mat[i][i+3] = 1.0;
  for (i=4; i<=n; ++i) a_mat[i][i-3] = 1.0;
  //
  for (i=1; i<=n; ++i)
    {
      s = 0.0;
      for (j=1; j<=n; ++j) s += a_mat[i][j] * (double)j;
      b_vec[i] = s;
    }
}

main(void)
{
  int n_mat;
  int i;
  double a_mat[NMAX+1][NMAX+1], b_vec[NMAX+1], x_vec[NMAX+1];
  //
  data_sd(&n_mat, a_mat, b_vec);
  sd_method(n_mat, a_mat, b_vec, x_vec);
  printf("# solution \n");
  for (i=1; i<=n_mat; ++i)
    {
      if (i%5==1) printf("# ");
      printf("%12.5e ", x_vec[i]);
      if (i%5==0) printf("\n");
    }
  printf("\n");
  //
  return 0;
}
