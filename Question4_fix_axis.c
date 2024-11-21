#include <gsl\gsl_blas.h>
#include <stdio.h>
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
void Roty(double alpha, gsl_matrix* Ry) {
    gsl_matrix_set(Ry, 0, 0, cos(alpha));
    gsl_matrix_set(Ry, 0, 1, 0);
    gsl_matrix_set(Ry, 0, 2, sin(alpha));
    gsl_matrix_set(Ry, 1, 0, 0);
    gsl_matrix_set(Ry, 1, 1, 1);
    gsl_matrix_set(Ry, 1, 2, 0);
    gsl_matrix_set(Ry, 2, 0, -sin(alpha));
    gsl_matrix_set(Ry, 2, 1, 0);
    gsl_matrix_set(Ry, 2, 2, cos(alpha));
}
int main() {
    double k[] = { 7,8,9 };
    double kx, ky, kz;
    kx = k[0];ky = k[1];kz = k[2];
    double alpha = atan2(kz, kx);
    double belta = atan2(ky, sqrt(pow(kx,2)+pow(kz,2)));
    gsl_matrix* Rx = gsl_matrix_alloc(3, 3);
    gsl_matrix* Ry = gsl_matrix_alloc(3, 3);
    gsl_matrix* Rz = gsl_matrix_alloc(3, 3);
    gsl_matrix* Ry_N = gsl_matrix_alloc(3, 3);
    gsl_matrix* Rz_N = gsl_matrix_alloc(3, 3);
    gsl_matrix* Rot = gsl_matrix_alloc(3, 3);
    double theta = PI / 4;
    Rotx(theta, Rx);
    Roty(alpha, Ry);
    Rotz(belta, Rz);
    Roty(-alpha, Ry_N);
    Rotz(-belta, Rz_N);
    //gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, Rz, Ry, 0.0, Rot);
    //gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, Rx, Rot, 0.0, Rot);
    //gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, Rz_N, Rot, 0.0, Rot);
    //gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, Ry_N, Rot, 0.0, Rot);
    
    gsl_matrix* result = gsl_matrix_alloc(3, 3);
    gsl_matrix_set_identity(result); // 设置为单位矩阵
    // 临时矩阵存储中间结果
    gsl_matrix* temp = gsl_matrix_alloc(3, 3);

    gsl_matrix* matrices[] = { Ry, Rz_N, Rx, Rz, Ry_N };
    for (int i = 0; i < 5; i++) {
        gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0 ,matrices[i] , result, 0.0, temp);
        gsl_matrix_memcpy(result, temp); // 将temp拷贝到result
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%8.4f ", gsl_matrix_get(result, i, j));
        }
        printf("\n");
    }
    return 0;
}

