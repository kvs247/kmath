#include <gtest/gtest.h>
#include <kmath/Constants.hpp>
#include <kmath/Ops.hpp>
#include <kmath/Trig.hpp>
#include <kmath/Utils.hpp>

static const double SQRT2 = kmath::sqrt(2);
static const double SQRT3 = kmath::sqrt(3);

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

TEST(Trig, Cosine)
{
  EXPECT_TRUE(kmath::floatEqual(kmath::cos(0.0), 1.0));
  EXPECT_TRUE(kmath::floatEqual(kmath::cos(kmath::pi / 6), SQRT3 / 2));
  EXPECT_TRUE(kmath::floatEqual(kmath::cos(kmath::pi / 4), SQRT2 / 2));
  EXPECT_TRUE(kmath::floatEqual(kmath::cos(kmath::pi / 3), 1.0 / 2));
  EXPECT_TRUE(kmath::floatEqual(kmath::cos(kmath::pi / 2), 0.0));
  EXPECT_TRUE(kmath::floatEqual(kmath::cos(kmath::pi), -1.0));
  EXPECT_EQ(kmath::cos(kmath::pi - kmath::pi / 4), kmath::cos(kmath::pi + kmath::pi / 4));
}

// TEST(Trig, Sine)
// {
//   EXPECT_TRUE(kmath::floatEqual(kmath::sin(0.0), 0.0));
//   EXPECT_TRUE(kmath::floatEqual(kmath::sin(30.0), 1.0 / 2));
//   EXPECT_TRUE(kmath::floatEqual(kmath::sin(45.0), SQRT2 / 2));
//   EXPECT_TRUE(kmath::floatEqual(kmath::sin(60.0), SQRT3 / 2));
//   EXPECT_TRUE(kmath::floatEqual(kmath::sin(90.0), 1.0));
//   EXPECT_TRUE(kmath::floatEqual(kmath::sin(270.0), -1.0));
//   EXPECT_EQ(kmath::cos(135.0), kmath::sin(225.0));
// }