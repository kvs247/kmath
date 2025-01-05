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

  return kmath::abs(a - b) < relTol * kmath::min(kmath::abs(a), kmath::abs(b));
}
} // namespace kmath