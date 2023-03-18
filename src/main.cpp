
#include "QProblem.h"

#include <iostream>

int main() {
    // qpTBR::Matrix A(3, 3, 1.0);
    // A.addToDiag(2);
    // A.print("A");
    // qpTBR::Matrix B(3, 1, 1.0);
    // B.print("B");
    // qpTBR::solveLinearSystem(A, B);
    // std::cout << std::endl;
    // for (int i = 0; i < B.getRows(); i++) {
    //     std::cout << B.getFull()[i] << " ";
    // }
    // std::cout << std::endl;

    // A.print("A");
    // B.print("B");
    // qpTBR::Matrix C(3, 1, 1.0);
    // A.multiply(1.0, B, 1.0, C);
    // C.print("C");

    qpTBR::Matrix G(2, 2, 0.0);
    G.addToDiag(1);
    qpTBR::Matrix A(1, 2, 1.0);
    qpTBR::Matrix b(1, 1, 1.0);
    qpTBR::Matrix c(2, 1, 0.0);
    qpTBR::Matrix x0(2, 1, 0.0);

    // A.print("A");
    // x0.print("x0");
    // A.multiply(1.0, x0, 0.0, b);
    // b.print("b");
    qpTBR::Matrix solution(c.getRows() + b.getRows(), 1, 0.0);

    qpTBR::ReturnValue ret = qpTBR::solveEQP(G, c, A, b, x0, solution);
    if (ret != qpTBR::ReturnValue::SUCCESS) {
        std::cout << "Error EQP" << std::endl;
    }
    solution.print("solution");

    return 0;
}