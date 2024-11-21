#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_vector_complex.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <math.h>
#define PI 3.14159265
void Rotz(double theta, gsl_matrix* Rz) {
    gsl_matrix_set(Rz, 0, 0, cos(theta));
    gsl_matrix_set(Rz, 0, 1, -sin(theta));
    gsl_matrix_set(Rz, 0, 2, 0);
    gsl_matrix_set(Rz, 1, 0, sin(theta));
    gsl_matrix_set(Rz, 1, 1, cos(theta));
    gsl_matrix_set(Rz, 1, 2, 0);
    gsl_matrix_set(Rz, 2, 0, 0);
    gsl_matrix_set(Rz, 2, 1, 0);
    gsl_matrix_set(Rz, 2, 2, 1);
}

void Rotx(double alpha, gsl_matrix* Rx) {
    gsl_matrix_set(Rx, 0, 0, 1);
    gsl_matrix_set(Rx, 0, 1, 0);
    gsl_matrix_set(Rx, 0, 2, 0);
    gsl_matrix_set(Rx, 1, 0, 0);
    gsl_matrix_set(Rx, 1, 1, cos(alpha));
    gsl_matrix_set(Rx, 1, 2, -sin(alpha));
    gsl_matrix_set(Rx, 2, 0, 0);
    gsl_matrix_set(Rx, 2, 1, sin(alpha));
    gsl_matrix_set(Rx, 2, 2, cos(alpha));
}

int main() {
    gsl_matrix* Rx = gsl_matrix_alloc(3, 3);
    gsl_matrix* Rz = gsl_matrix_alloc(3, 3);
    gsl_matrix* Rot=gsl_matrix_alloc(3,3);
    Rotx(PI / 6, Rx);
    Rotz(PI / 4, Rz);

    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans,1.0, Rx, Rz,0.0, Rot);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%8.4f ", gsl_matrix_get(Rot, i, j));
        }
        printf("\n");
    }
    gsl_matrix_free(Rx);
    gsl_matrix_free(Rz);
    return 0;
}