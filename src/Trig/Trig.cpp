#include <iostream>
#include <kmath/Constants.hpp>
#include <kmath/Trig.hpp>

namespace kmath
{
double degToRad(double x)
{

  x *= kmath::pi / 180;

  while (x > kmath::pi)
  {
    x -= 2 * kmath::pi;
  }

  while (x <= -kmath::pi)
  {
    x += 2 * kmath::pi;
  }

  return x;
}

double radToDeg(double x)
{
  x *= 180.0 / kmath::pi;

  while (x > 180.0)
  {
    x -= 360.0;
  }

  while (x <= -180.0)
  {
    x += 360.0;
  }

  return x;
}

double cos(double x)
{
  const double xx = x * x;
  const double res = 1 - xx / 2 + xx * xx / 12 - xx * xx * xx / 720;
  std::cout << res << "\n";
  return res;
}

double sin(double x) {}
double tan(double x) {}
} // namespace kmath