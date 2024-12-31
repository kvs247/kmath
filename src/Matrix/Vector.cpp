#include <kmath/Matrix/Vector.hpp>
#include <kmath/Ops.hpp>
#include <numeric>
#include <vector>

Vector::Vector(const std::vector<double> &eles) : Matrix(eles, eles.size(), 1) {}

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

double Vector::innerProduct(Vector &other)
{
  if (this->nRows != other.nRows)
  {
    throw std::invalid_argument("Vectors of inner product must have equal length");
  }

  double res = 0.0;
  for (size_t i = 0; i < this->nRows; ++i)
  {
    res += this->data[i] * other.data[i];
  }

  return res;
}