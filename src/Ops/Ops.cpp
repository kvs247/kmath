#include <kmath/Ops.hpp>
#include <stdexcept>

namespace kmath
{
double abs(double x) { return (x > 0) ? x : -x; }

double sqrt(double x)
{
  if (x < 0)
  {
    throw std::invalid_argument("sqrt() input must be non-negative");
  }

  if (x == 0 || x == 1)
  {
    return x;
  }

  static const double tol = 1e-15;
  double sqrtx = x / 2;

  while (true)
  {
    double next = (sqrtx + x / sqrtx) / 2;
    if (abs(sqrtx - next) / next < tol)
    {
      return next;
    }
    sqrtx = next;
  }
}
} // namespace kmath