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

  size_t size() const { return data.size(); }
  double at(size_t i) const { return Matrix::at(i, 0); }

  Vector &normalize();
  Vector normalize() const;

  double innerProduct(const Vector &) const;

  Vector &proj(const Vector &);
  Vector proj(const Vector &) const;

  Vector &operator=(const Vector &);
  Vector &operator+=(const Vector &);
  Vector operator+(const Vector &) const;
  Vector &operator-=(const Vector &);
  Vector operator-(const Vector &) const;
  Vector &operator*=(const Vector &) = delete;
  Vector operator*(const Vector &) = delete;
};