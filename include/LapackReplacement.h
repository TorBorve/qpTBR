#pragma once


#define LAPACK_DGETRF dgetrf_
#define LAPACK_DGETRS dgetrs_

extern "C" {
    void LAPACK_DGETRF(int *m, int *n, double *A, int *lda, int *ipiv, int *info);
    void LAPACK_DGETRS(char *trans, int *n, int *nrhs, double *A, int *lda, int *ipiv, double *b, int *ldb, int *info);
}