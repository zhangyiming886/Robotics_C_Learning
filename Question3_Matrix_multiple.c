#include<stdio.h>
#include<gsl/gsl_blas.h>
#define PI 3.14159265
void main(void)
{
	double a[] = { 0.11,0.12,0.13,
	0.21,0.22,0.23 };
	double b[] = { 1011,1012,
	1021,1022,
	1031,1032 };
	double c[] = { 0.00,0.00,
	0.00,0.00 };
	gsl_matrix_view A = gsl_matrix_view_array(a, 2, 3);
	gsl_matrix_view B = gsl_matrix_view_array(b, 3, 2);
	gsl_matrix_view C = gsl_matrix_view_array(c, 2, 2);
	/*ComputeC=AB*/
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans,
		1.0, &A.matrix, &B.matrix,
		0.0, &C.matrix);
	printf("[%g, %g\n", c[0], c[1]);
	printf(" %g, %g ]\n", c[2], c[3]);
	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < 3;j++) {
			printf("%g	", gsl_matrix_get(&A.matrix, i, j));
		}
		printf("\n");
	}
	return 0;
}