#include <kmath/Ops.hpp>
#include <kmath/Utils.hpp>

namespace kmath
{
bool floatEqual(const double a, const double b, const double relTol)
{
  if (a == b)
  {
    return true;
  }

  if (a == 0.0 || b == 0.0)
  {
    const auto nonZero = (a == 0.0) ? b : a;
    return kmath::abs(nonZero) < relTol;
  }

  return kmath::abs(a - b) < relTol * kmath::min(kmath::abs(a), kmath::abs(b));
}
} // namespace kmath