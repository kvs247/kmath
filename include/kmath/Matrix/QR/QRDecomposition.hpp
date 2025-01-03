#pragma once

#include <utility>

#include "../Matrix.hpp"

class QRDecomposition
{
public:
  virtual ~QRDecomposition() = default;
  virtual std::pair<Matrix, Matrix> decomp(const Matrix &) const = 0;
};
