#pragma once

#include "Matrix.h"

namespace qpTBR {

ReturnValue solveLinearSystem(const Matrix &A, Matrix &b);

} // namespace qpTBR