#pragma once

#include <initializer_list>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <stdlib.h>
#include <vector>

class Vector;

class Matrix
{
public:
  Matrix() = delete;
  Matrix(const Matrix &) = default;
  Matrix(const std::vector<Vector> &cols);
  Matrix(const std::vector<std::vector<double>> &rows);
  Matrix(const std::vector<double> &eles, const size_t rows, const size_t cols);

  size_t getNRows() const;
  size_t getNCols() const;
  std::vector<std::shared_ptr<Vector>> getRows() const;
  std::vector<std::shared_ptr<Vector>> getCols() const;
  std::vector<double> getData() const;
  std::vector<double> getDiagonal() const;

  bool isSquare() const;

  static bool isSameDimension(const Matrix &, const Matrix &);
  static Matrix makeIdentityMatrix(const size_t n);

  void print(std::ostream &os = std::cout) const;
  double at(size_t i, size_t j) const;
  Matrix &transpose();
  Matrix transpose() const;

  bool operator==(const Matrix &) const;
  bool operator!=(const Matrix &) const;
  Matrix &operator=(const Matrix &);
  Matrix &operator+=(const Matrix &);
  Matrix operator+(const Matrix &) const;
  Matrix &operator-=(const Matrix &);
  Matrix operator-(const Matrix &) const;
  Matrix &operator*=(const Matrix &);
  Matrix operator*(const Matrix &) const;

protected:
  std::vector<double> data;
  size_t nRows = 0;
  size_t nCols = 0;
};
