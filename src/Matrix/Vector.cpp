#include <algorithm>
#include <kmath/Matrix/Vector.hpp>
#include <kmath/Ops.hpp>
#include <numeric>
#include <vector>

// constructors
Vector::Vector(const std::vector<double> &eles) : Matrix(eles, eles.size(), 1) {}

// public methods
Vector &Vector::normalize()
{
  double n = kmath::sqrt(
      std::accumulate(this->data.cbegin(), this->data.cend(), 0.0, [](double s, double x) { return s + x * x; }));

  if (n == 0)
  {
    return *this;
  }

  for (auto &x : this->data)
  {
    x /= n;
  }

  return *this;
}

Vector Vector::normalize() const { return Vector(*this).normalize(); }

double Vector::innerProduct(const Vector &u) const
{
  if (this->nRows != u.nRows)
  {
    throw std::invalid_argument("Vectors of inner product must have equal length");
  }

  double res = 0.0;
  for (size_t i = 0; i < this->nRows; ++i)
  {
    res += this->data[i] * u.data[i];
  }

  return res;
}

Vector &Vector::proj(const Vector &u)
{
  const auto uu = u.innerProduct(u); // throws exception if Vs are unequal length
  if (uu == 0)
  {
    this->data = std::vector(u.nRows, 0.0);
    return *this;
  }

  const auto uv = this->innerProduct(u);

  std::transform(u.data.cbegin(), u.data.cend(), this->data.begin(), [&](double x) { return x * uv / uu; });

  for (auto x : this->data)
  {
    std::cout << x << " ";
  }
  std::cout << "\n";

  return *this;
}

Vector Vector::proj(const Vector &u) const { return Vector(*this).proj(u); }

// operators
Vector &Vector::operator=(const Vector &other)
{
  Matrix::operator=(other);
  return *this;
}

Vector &Vector::operator+=(const Vector &other)
{
  Matrix::operator+=(other);
  return *this;
}

Vector Vector::operator+(const Vector &other) const { return Vector(*this) += other; }

Vector &Vector::operator-=(const Vector &other)
{
  Matrix::operator-=(other);
  return *this;
}

Vector Vector::operator-(const Vector &other) const { return Vector(*this) -= other; }