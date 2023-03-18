#pragma once


#define LAPACK_DGETRF dgetrf_
#define LAPACK_DGETRS dgetrs_
#define LAPACK_DGEMM dgemm_

extern "C" {
    void LAPACK_DGETRF(int *m, int *n, double *A, int *lda, int *ipiv, int *info);
    void LAPACK_DGETRS(char *trans, int *n, int *nrhs, double *A, int *lda, int *ipiv, double *b, int *ldb, int *info);
    void LAPACK_DGEMM(char *transa, char *transb, int *m, int *n, int *k, double *alpha, double *A, int *lda, double *B, int *ldb, double *beta, double *C, int *ldc);
}