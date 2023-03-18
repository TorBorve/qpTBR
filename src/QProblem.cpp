#include "QProblem.h"
#include "LapackReplacement.h"

namespace qpTBR {

ReturnValue solveLinearSystem(const Matrix &A, Matrix &b) {
    if (A.getRows() != A.getCols()) {
        return ReturnValue::FAILURE;
    }
    if (b.getCols() > 1) {
        // TODO: implement for multiple right hand sides. Error due to row major storage.
        return ReturnValue::FAILURE;
    }
    Matrix A_copy = A.duplicate();
    int M = A.getRows();
    int N = A.getCols();
    int LDA = A.getRows();
    int INFO;
    int IPIV[M];
    LAPACK_DGETRF(&M, &N, A_copy.getFull(), &LDA, IPIV, &INFO);
    if (INFO != 0) {
        return ReturnValue::FAILURE;
    }
    char TRANS = 'T';
    int NRHS = 1;
    int LDB = b.getRows();
    LAPACK_DGETRS(&TRANS, &N, &NRHS, A_copy.getFull(), &LDA, IPIV, b.getFull(), &LDB, &INFO);
    if (INFO != 0) {
        return ReturnValue::FAILURE;
    }
    return ReturnValue::SUCCESS;
}

} // namespace qpTBR