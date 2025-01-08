#include <cmath> // no!!!
#include <iostream>
#include <kmath/Constants.hpp>
#include <kmath/Ops.hpp>
#include <kmath/Trig.hpp>
#include <stdexcept>

namespace kmath
{
// return radians in range (-π, π]
double reduceRad(double x)
{
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

// return degrees in range (-180, 180]
double reduceDeg(double x)
{
  while (x > 180)
  {
    x -= 360;
  }

  while (x <= -180)
  {
    x += 360;
  }

  return x;
}

double degToRad(double x)
{
  x *= kmath::pi / 180;

  return reduceRad(x);
}

double radToDeg(double x)
{
  x *= 180.0 / kmath::pi;

  return reduceDeg(x);
}

std::pair<double, double> polarToCart(double r, double t) { return {r * cos(t), r * sin(t)}; }

std::pair<double, double> cartToPolar(double x, double y)
{
  // use own atan() when implemented
  double t = std::atan2(y, x);

  // use euclidnorm()/hypot() when implemented
  double r = kmath::sqrt(x * x + y * y);

  return {r, t};
}

double cos(double x)
{
  static const double tol = 1e-15;

  x = reduceRad(x);

  double next;
  double res = 1;
  double xx = x * x;

  double lastNum = 1;
  double lastDen = 1;
  int lastFact = 0;
  int sign = 1;

  while (true)
  {
    if (lastFact > 100)
    {
      throw std::runtime_error("Cosine Taylor series did not converge after 50 terms");
    }

    lastFact += 2;
    lastNum *= xx;
    lastDen *= (lastFact * (lastFact - 1));
    sign *= -1;

    next = sign * lastNum / lastDen;
    res += next;

    if (kmath::abs(next) < tol)
    {
      return res;
    }
  }
}

double sin(double x)
{
  static const double tol = 1e-15;

  x = reduceRad(x);

  double next;
  double res = x;
  double xx = x * x;

  double lastNum = x;
  double lastDen = 1;
  int lastFact = 1;
  int sign = 1;

  while (true)
  {
    if (lastFact > 100)
    {
      throw std::runtime_error("Cosine Taylor series did not converge after 50 terms");
    }

    lastFact += 2;
    lastNum *= xx;
    lastDen *= (lastFact * (lastFact - 1));
    sign *= -1;

    next = sign * lastNum / lastDen;
    res += next;

    if (kmath::abs(next) < tol)
    {
      return res;
    }
  }
}
} // namespace kmath