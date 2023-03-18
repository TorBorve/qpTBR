#pragma once

#include <string>

namespace qpTBR {

using real_t = double;

enum class ReturnValue {
    SUCCESS,
    FAILURE
};


class Matrix {
public:
    Matrix() : rows{0}, cols{0}, val{nullptr} {}
    Matrix(int rows, int cols, real_t startValue);
    Matrix(int rows, int cols, real_t *val) : rows{rows}, cols{cols}, val{val} {}
    ~Matrix();

    real_t* getFull() { return val; }
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    Matrix duplicate() const;
    ReturnValue addToDiag(real_t alpha);
    ReturnValue print(std::string name) const;
private:
    int rows;
    int cols;
    real_t *val;
};

} // namespace qpTBR