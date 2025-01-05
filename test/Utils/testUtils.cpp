#include <gtest/gtest.h>
#include <kmath/Utils.hpp>

TEST(Utils, FloatEquality)
{
  const double a = 2.999999999999824;
  const double b = 3.000000000000000;

  EXPECT_TRUE(kmath::floatEqual(a, b));
  EXPECT_TRUE(kmath::floatEqual(0.0, 0.0));
  EXPECT_FALSE(kmath::floatEqual(1.0, 0.9995));
  EXPECT_FALSE(kmath::floatEqual(987654321.123456789, 9.8));
}