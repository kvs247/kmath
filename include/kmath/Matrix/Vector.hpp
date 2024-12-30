#pragma once

#include <vector>

#include "Matrix.hpp"

class Vector : public Matrix
{
public:
  Vector() = delete;
  Vector(const Vector &) = default;
  Vector(const std::vector<double> &);

  std::vector<double> getDiagonal() const = delete;

  double at(size_t i) const { return Matrix::at(i, 1); }

private:
  const size_t nCols = 1;
};