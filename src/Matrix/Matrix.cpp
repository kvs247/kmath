#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <kmath/Matrix/Matrix.hpp>
#include <kmath/Matrix/Vector.hpp>
#include <kmath/Utils.hpp>
#include <memory>
#include <span>
#include <stdexcept>
#include <vector>

// constructors
Matrix::Matrix(const std::vector<Vector> &cols) : nRows(cols.begin()->size()), nCols(cols.size())
{
  if (!cols.size())
  {
    throw std::invalid_argument("Matrix cannot be empty");
  }

  data.resize(nRows * nCols);

  for (size_t i = 0; i < nCols; ++i)
  {
    const auto col = cols[i];
    if (col.size() != nRows)
    {
      throw std::invalid_argument("Matrix columns must have the same length");
    }
    for (size_t j = 0; j < nRows; ++j)
    {
      data[j * nCols + i] = cols[i].at(j);
    }
  }
};

Matrix::Matrix(const std::vector<std::vector<double>> &rows) : nRows(rows.size()), nCols(rows.begin()->size())
{
  if (!rows.size())
  {
    throw std::invalid_argument("Matrix cannot be empty");
  }

  data.reserve(nRows * nCols);
  auto dataIt = data.begin();

  for (auto it = rows.begin(); it != rows.end(); ++it)
  {
    const auto row = *it;
    if (row.size() != nCols)
    {
      throw std::invalid_argument("Matrix rows must have the same length");
    }

    data.insert(dataIt, row.cbegin(), row.cend());
    dataIt += nCols;
  }
}

Matrix::Matrix(const std::vector<double> &eles, const size_t rows, const size_t cols)
    : nRows(rows), nCols(cols), data(eles)
{
  if (data.size() != rows * cols)
  {
    throw std::invalid_argument("Matrix of dimension n x m must have (n*m) elements");
  }
}

// getters
size_t Matrix::getNRows() const { return nRows; }
size_t Matrix::getNCols() const { return nCols; }

std::vector<std::shared_ptr<Vector>> Matrix::getRows() const
{
  std::vector<std::shared_ptr<Vector>> rows(nRows);

  for (size_t i = 0; i < nRows; ++i)
  {
    auto row = std::make_shared<Vector>(std::vector<double>(nCols, 0.0));
    for (size_t j = 0; j < nCols; ++j)
    {
      row->data[j] = data[j + nCols * i];
    }
    rows[i] = row;
  }

  return rows;
}

std::vector<std::shared_ptr<Vector>> Matrix::getCols() const
{
  std::vector<std::shared_ptr<Vector>> cols(nCols);

  for (size_t i = 0; i < nCols; ++i)
  {
    auto col = std::make_shared<Vector>(std::vector<double>(nRows, 0.0));
    for (size_t j = 0; j < nRows; ++j)
    {
      col->data[j] = data[i + j * nCols];
    }
    cols[i] = col;
  }

  return cols;
}

std::vector<double> Matrix::getData() const { return data; }

std::vector<double> Matrix::getDiagonal() const
{
  if (!this->isSquare())
  {
    throw std::invalid_argument("Cannot get diagonal of non-square matrix");
  }

  std::vector<double> res(nCols);
  for (size_t i = 0; i < nCols; ++i)
  {
    res[i] = this->at(i, i);
  }
  return res;
}

bool Matrix::isSquare() const { return this->nRows == this->nCols; }

bool Matrix::isSameDimension(const Matrix &m1, const Matrix &m2)
{
  return m1.nRows == m2.nRows && m1.nCols == m2.nCols;
}

Matrix Matrix::makeIdentityMatrix(const size_t n)
{
  std::vector<double> data(n * n, 0.0);
  for (size_t i = 0; i < n; ++i)
  {
    data[i * n + i] = 1.0;
  }
  return Matrix(data, n, n);
}

// public methods
void Matrix::print(std::ostream &os) const
{
  const auto origFlags(os.flags());
  const auto origPrecision = os.precision();
  os << std::fixed << std::setprecision(2);

  for (size_t i = 0; i < data.size(); ++i)
  {
    if (i % nCols == 0)
    {
      os << "|";
    }

    os << std::setw(8) << data[i];

    if ((i + 1) % nCols == 0)
    {
      os << " |\n";
    }
  }

  os.flags(origFlags);
  os.precision(origPrecision);
}

double Matrix::at(size_t i, size_t j) const
{
  if (i >= this->nRows || j >= this->nCols)
  {
    throw std::out_of_range("Matrix index is outside of valid range");
  }

  return data[j + i * nCols];
}

// should do this without using `newData` intermediate memory
Matrix &Matrix::transpose()
{
  std::vector<double> newData;
  newData.reserve(nCols * nRows);

  for (size_t i = 0; i < nCols; ++i)
  {
    for (size_t j = 0; j < nRows; ++j)
    {
      newData.push_back(data[i + j * nCols]);
    }
  }

  this->data = newData;
  std::swap(this->nRows, this->nCols);

  return *this;
}

Matrix Matrix::transpose() const
{
  std::vector<double> newData;
  newData.reserve(nCols * nRows);

  for (size_t i = 0; i < nCols; ++i)
  {
    for (size_t j = 0; j < nRows; ++j)
    {
      newData.push_back(data[i + j * nCols]);
    }
  }

  return Matrix(newData, nCols, nRows);
}

// operators
bool Matrix::operator==(const Matrix &other) const
{
  if (!isSameDimension(*this, other))
  {
    return false;
  }

  for (size_t i = 0; i < this->data.size(); ++i)
  {
    if (!kmath::floatEqual(this->data[i], other.data[i]))
    {
      return false;
    }
  }

  return true;
};

bool Matrix::operator!=(const Matrix &other) const { return !(*this == other); }

Matrix &Matrix::operator=(const Matrix &other)
{
  this->data = other.data;
  this->nRows = other.nRows;
  this->nCols = other.nCols;

  return *this;
}

Matrix &Matrix::operator+=(const Matrix &other)
{
  if (!Matrix::isSameDimension(*this, other))
  {
    throw std::invalid_argument("Matrices must be equal dimension for addition");
  };

  for (size_t i = 0; i < this->data.size(); ++i)
  {
    this->data[i] = this->data[i] + other.data[i];
  }

  return *this;
};

Matrix Matrix::operator+(const Matrix &other) const { return Matrix(*this) += other; }

Matrix &Matrix::operator-=(const Matrix &other)
{
  if (!Matrix::isSameDimension(*this, other))
  {
    throw std::invalid_argument("Matrices must be equal dimension for subtraction");
  };

  std::vector<double> differenceData(this->data.size());
  for (size_t i = 0; i < this->data.size(); ++i)
  {
    this->data[i] = this->data[i] - other.data[i];
  }

  return *this;
}

Matrix Matrix::operator-(const Matrix &other) const { return Matrix(*this) -= other; }

Matrix &Matrix::operator*=(const Matrix &other)
{
  if (this->nCols != other.nRows)
  {
    throw std::invalid_argument("Invalid shapes for matrix multiplication");
  }

  const auto newNRows = this->nRows;
  const auto newNCols = other.nCols;
  auto newData = std::vector<double>(newNRows * newNCols, 0.0);

  for (size_t row = 0; row < newNRows; ++row)
  {
    for (size_t k = 0; k < this->nCols; ++k)
    {
      const auto thisMatrixValue = this->at(row, k);
      for (size_t col = 0; col < newNCols; ++col)
      {
        newData[col + newNCols * row] += thisMatrixValue * other.at(k, col);
      }
    }
  }

  this->nRows = newNRows;
  this->nCols = newNCols;
  this->data = std::move(newData);

  return *this;
}

Matrix Matrix::operator*(const Matrix &other) const { return Matrix(*this) *= other; }
