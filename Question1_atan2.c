#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_vector_complex.h>
#include <math.h>
#include <openblas/cblas.h>
#define PI 3.14159265

int main() {
	double a = atan2(1, 1) / PI * 180;
	printf("%f", a);
	return 0;
}
