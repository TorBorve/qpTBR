#include "QProblem.h"
#include "LapackReplacement.h"

#include <cstring>

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

ReturnValue solveEQP(const Matrix &G, const Matrix &c, const Matrix &A, const Matrix &b, const Matrix &x0, Matrix &solution) {
    if (G.getRows() != G.getCols()) {
        return ReturnValue::FAILURE;
    }
    if (A.getRows() != b.getRows()) {
        return ReturnValue::FAILURE;
    }
    if (b.getCols() > 1) {
        return ReturnValue::FAILURE;
    }
    if (A.getCols() != x0.getRows()) {
        return ReturnValue::FAILURE;
    }
    if (x0.getRows() != c.getRows()) {
        return ReturnValue::FAILURE;
    }
    if (solution.getCols() != 1 || solution.getRows() != c.getRows() + b.getRows()) {
        return ReturnValue::FAILURE;
    }

    real_t* AValKKT = new real_t[(A.getRows()+G.getRows())*(G.getCols()+A.getRows())]{0.0};
    real_t* bValKKT = solution.getFull(); //new real_t[c.getRows() + b.getRows()];
    std::memcpy(bValKKT, c.getFull(), c.getRows()*sizeof(real_t));
    std::memcpy(bValKKT + c.getRows(), b.getFull(), b.getRows()*sizeof(real_t));
    Matrix g{c.getRows(), 1, bValKKT};
    Matrix h{b.getRows(), 1, bValKKT + c.getRows()};
    G.multiply(1.0, x0, 1.0, g);
    A.multiply(1.0, x0, -1.0, h);
    for (int i = 0; i < G.getRows(); i++) {
        std::memcpy(AValKKT + i*(G.getCols()+A.getRows()), G.getFull() + i*G.getCols(), G.getCols()*sizeof(real_t));
        for (int j = 0; j < A.getRows(); j++) {
            AValKKT[i*(G.getCols()+A.getRows()) + j + G.getCols()] = A.getFull()[j*A.getRows() + i];
        }
    }
    for (int i = 0; i < A.getRows(); i++) {
        for (int j = 0; j < A.getCols(); j++) {
            AValKKT[(i+G.getRows())*(G.getCols()+A.getRows()) + j] = A.getFull()[i*A.getCols() + j];
        }
    }
    Matrix AKKT{G.getRows() + A.getRows(), G.getCols() + A.getRows(), AValKKT};
    Matrix bKKT{c.getRows() + b.getRows(), 1, bValKKT};
    return solveLinearSystem(AKKT, bKKT);
}
} // namespace qpTBR