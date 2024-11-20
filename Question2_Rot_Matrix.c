#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_vector_complex.h>
#include <gsl/gsl_matrix.h>
#include <math.h>
#define PI 3.14159265

void rot_matrix(double theta)
{
	gsl_matrix *rot = gsl_matrix_alloc(2, 2);
	gsl_matrix_set(rot, 0, 0, cos(theta));
	gsl_matrix_set(rot, 1, 0, sin(theta));
	gsl_matrix_set(rot, 0, 1, -sin(theta));
	gsl_matrix_set(rot, 1, 1, cos(theta));
	for (int i = 0;i < 2;i++) {
		for (int j = 0;j < 2;j++) {
			printf("%g		", gsl_matrix_get(rot, i, j));
		}
		printf("\n");
	}
}
int main() {
	rot_matrix(PI/6);
	return 0;
}
