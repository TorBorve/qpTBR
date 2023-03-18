#include "Matrix.h"
#include "LapackReplacement.h"

#include <iostream>
#include <cstring>

namespace qpTBR {

Matrix::Matrix(int rows, int cols, real_t startValue) : rows{rows}, cols{cols}, val{new real_t[rows*cols]} {
    for (int i = 0; i < rows*cols; i++) {
        this->val[i] = startValue;
    }
}
Matrix::~Matrix() {
    if (val != nullptr) {
        // delete[] val;
    }
}

ReturnValue Matrix::addToDiag(real_t alpha) {
    if (rows != cols) {
        return ReturnValue::FAILURE;
    }
    for (int i = 0; i < rows; i++) {
        val[i*rows + i] += alpha;
    }
    return ReturnValue::SUCCESS;
}
ReturnValue Matrix::print(std::string name) const {
    std::cout << name << " = [" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << val[i*cols + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "]" << std::endl;
    return ReturnValue::SUCCESS;
}

Matrix Matrix::duplicate() const {
    real_t *newVal = new real_t[rows*cols];
    std::memcpy(newVal, val, rows*cols*sizeof(real_t));
    return Matrix(rows, cols, newVal);
}

ReturnValue Matrix::multiply(real_t alpha, const Matrix &x, real_t beta, Matrix &y) const {
    if (rows != y.rows || x.rows != cols || y.cols > 1) {
        return ReturnValue::FAILURE;
    }
    char transA = 'T';
    char transB = 'N';
    int M = rows;
    int N = y.cols;
    int K = cols;
    int LDA = cols;
    int LDB = x.rows;
    int LDC = y.rows;
    LAPACK_DGEMM(&transA, &transB, &M, &N, &K, &alpha, val, &LDA, x.val, &LDB, &beta, y.val, &LDC);
    return ReturnValue::SUCCESS;
}

} // namespace qpTBR