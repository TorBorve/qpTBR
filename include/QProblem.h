#pragma once

#include "Matrix.h"

namespace qpTBR {

ReturnValue solveLinearSystem(const Matrix &A, Matrix &b);

ReturnValue solveEQP(const Matrix &G, const Matrix &c, const Matrix &A, const Matrix &b, const Matrix &x0, Matrix &solution);

} // namespace qpTBR