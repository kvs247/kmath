#include <gtest/gtest.h>
#include <kmath/Ops.hpp>
#include <stdexcept>

TEST(Ops, Abs)
{
  EXPECT_EQ(kmath::abs(2), 2);
  EXPECT_EQ(kmath::abs(0), 0);
  EXPECT_EQ(kmath::abs(-2), 2);
}

TEST(Ops, SqrtNonnegative)
{
  EXPECT_EQ(kmath::sqrt(0), 0);
  EXPECT_EQ(kmath::sqrt(1), 1);
  EXPECT_EQ(kmath::sqrt(100), 10);

  const double SQRT2 = 1.4142135623730950488016887242096980785696718753769480731766796;
  EXPECT_TRUE(kmath::sqrt(2) - SQRT2 < 1e-15);
}

TEST(Ops, SqrtNegative) { EXPECT_THROW(kmath::sqrt(-1), std::invalid_argument); }