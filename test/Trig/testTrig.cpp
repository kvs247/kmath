#include <gtest/gtest.h>
#include <kmath/Constants.hpp>
#include <kmath/Ops.hpp>
#include <kmath/Trig.hpp>
#include <kmath/Utils.hpp>
#include <stdexcept>
#include <utility>

static const double tol = kmath::DEFAULT_FLOAT_RELATIVE_TOLERANCE;
static const double SQRT2 = kmath::sqrt(2);
static const double SQRT3 = kmath::sqrt(3);

TEST(Trig, ReduceRadians)
{
  EXPECT_EQ(kmath::reduceRad(kmath::pi), kmath::pi);
  EXPECT_EQ(kmath::reduceRad(3 * kmath::pi / 2), -kmath::pi / 2);
  EXPECT_EQ(kmath::reduceRad(-kmath::pi), kmath::pi);
}

TEST(Trig, ReduceDegrees)
{
  EXPECT_EQ(kmath::reduceDeg(180), 180);
  EXPECT_EQ(kmath::reduceDeg(270), -90);
  EXPECT_EQ(kmath::reduceDeg(-180), 180);
}

TEST(Trig, DegreesToRadians)
{
  EXPECT_EQ(kmath::degToRad(0.0), 0.0);
  EXPECT_EQ(kmath::degToRad(45.0), kmath::pi / 4);
  EXPECT_EQ(kmath::degToRad(315.0), -kmath::pi / 4);
  EXPECT_EQ(kmath::degToRad(450.0), kmath::pi / 2);
}

TEST(Trig, RadiansToDegree)
{
  EXPECT_EQ(kmath::radToDeg(0.0), 0.0);
  EXPECT_EQ(kmath::radToDeg(kmath::pi / 4), 45.0);
  EXPECT_EQ(kmath::radToDeg(7 * kmath::pi / 4), -45.0);
  EXPECT_EQ(kmath::radToDeg(5 * kmath::pi / 2), 90.0);
}

TEST(Trig, PolarToCartesian)
{
  EXPECT_NEAR(kmath::polarToCart(0.0, 0.0).first, 0.0, tol);
  EXPECT_NEAR(kmath::polarToCart(0.0, 0.0).second, 0.0, tol);

  const std::pair<double, double> cartPoint{-3.0 * SQRT3 / 2, 3.0 / 2};
  const std::pair<double, double> polarPoint{3.0, 5.0 * kmath::pi / 6};
  EXPECT_NEAR(kmath::polarToCart(polarPoint.first, polarPoint.second).first, cartPoint.first, tol);
  EXPECT_NEAR(kmath::polarToCart(polarPoint.first, polarPoint.second).second, cartPoint.second, tol);
}

TEST(Trig, cartesianToPolar)
{
  EXPECT_NEAR(kmath::cartToPolar(0.0, 0.0).first, 0.0, tol);
  EXPECT_NEAR(kmath::cartToPolar(0.0, 0.0).second, 0.0, tol);

  const std::pair<double, double> cartPoint{-3.0 * SQRT3 / 2, 3.0 / 2};
  const std::pair<double, double> polarPoint{3.0, 5.0 * kmath::pi / 6};
  EXPECT_NEAR(kmath::cartToPolar(cartPoint.first, cartPoint.second).first, polarPoint.first, tol);
  EXPECT_NEAR(kmath::cartToPolar(cartPoint.first, cartPoint.second).second, polarPoint.second, tol);
}

TEST(Trig, Cosine)
{
  EXPECT_NEAR(kmath::cos(0.0), 1.0, tol);
  EXPECT_NEAR(kmath::cos(kmath::pi / 6), SQRT3 / 2, tol);
  EXPECT_NEAR(kmath::cos(kmath::pi / 4), SQRT2 / 2, tol);
  EXPECT_NEAR(kmath::cos(kmath::pi / 3), 1.0 / 2, tol);
  EXPECT_NEAR(kmath::cos(kmath::pi / 2), 0.0, tol);
  EXPECT_NEAR(kmath::cos(kmath::pi), -1.0, tol);
  EXPECT_NEAR(kmath::cos(kmath::pi - kmath::pi / 4), kmath::cos(kmath::pi + kmath::pi / 4), tol);
}

TEST(Trig, Sine)
{
  EXPECT_NEAR(kmath::sin(0.0), 0.0, tol);
  EXPECT_NEAR(kmath::sin(kmath::pi / 6), 1.0 / 2, tol);
  EXPECT_NEAR(kmath::sin(kmath::pi / 4), SQRT2 / 2, tol);
  EXPECT_NEAR(kmath::sin(kmath::pi / 3), SQRT3 / 2, tol);
  EXPECT_NEAR(kmath::sin(kmath::pi / 2), 1.0, tol);
  EXPECT_NEAR(kmath::sin(3 * kmath::pi / 2), -1.0, tol);
  EXPECT_NEAR(kmath::sin(kmath::pi / 2 - kmath::pi / 4), kmath::sin(kmath::pi / 2 + kmath::pi / 4), tol);
}
