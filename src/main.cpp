
#include "QProblem.h"

#include <iostream>

int main() {
    qpTBR::Matrix A(3, 3, 1.0);
    A.addToDiag(2);
    A.print("A");
    qpTBR::Matrix B(3, 1, 1.0);
    B.print("B");
    qpTBR::solveLinearSystem(A, B);
    std::cout << std::endl;
    for (int i = 0; i < B.getRows(); i++) {
        std::cout << B.getFull()[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}