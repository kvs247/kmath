#include <gtest/gtest.h>
#include <kmath/Matrix/Vector.hpp>
#include <kmath/Ops.hpp>
#include <stdexcept>

// constructors
TEST(Vector, CanCreateVector)
{
  Vector v({1, 2, 3, 4});

  size_t expectedNRows = 4;
  size_t expectedNCols = 1;
  std::vector<double> expectedData{1.0, 2.0, 3.0};

  EXPECT_EQ(v.getNRows(), expectedNRows);
  EXPECT_EQ(v.getNCols(), expectedNCols);
}

TEST(Vector, AtWithValidInput)
{
  Vector v({1.0, 2.0, 3.0});

  EXPECT_EQ(v.at(0), 1.0);
  EXPECT_EQ(v.at(1), 2.0);
  EXPECT_EQ(v.at(2), 3.0);
}

TEST(Vector, Normalize)
{
  Vector v({1.0, -2.0, 3.0});

  const double n = kmath::sqrt(1.0 + 4.0 + 9.0);
  Vector expected({1.0 / n, -2.0 / n, 3.0 / n});

  {
    auto vNonConst = v;

    EXPECT_EQ(vNonConst.normalize(), expected);
    EXPECT_NE(vNonConst, v);
  }

  {
    const auto vConst = v;
    const auto vNorm = vConst.normalize();

    EXPECT_EQ(vNorm, expected);
    EXPECT_EQ(vConst, v);
  }
}

TEST(Vector, NormalizeZeroVector)
{
  Vector v({0.0, 0.0, 0.0});

  EXPECT_EQ(v.normalize(), v);
}

TEST(Vector, InnerProduct)
{
  Vector v1({0.5, 1.2, -3.14});
  Vector v2({0, 0.8, 9.8});

  double expectedResult = -29.812;

  EXPECT_EQ(v1.innerProduct(v2), expectedResult);
}

TEST(Vector, InnerProductInvalidInput)
{
  Vector v1({0.5, 1.2, -3.14});
  Vector v2({0, 0.8});

  EXPECT_THROW(v1.innerProduct(v2), std::invalid_argument);
}

TEST(Vector, Projection)
{
  Vector v({1.0, -2.0, 2.0});
  Vector u({4.0, 0.0, -3.0});

  Vector expected({-8.0 / 25, 0.0, 6.0 / 25});

  {
    auto vNonConst = v;

    EXPECT_EQ(vNonConst.proj(u), expected);
    EXPECT_NE(vNonConst, v);
  }

  {
    const auto vConst = v;
    auto vProj = vConst.proj(u);

    EXPECT_EQ(vProj, expected);
    EXPECT_EQ(vConst, v);
  }
}

TEST(Vector, ProjectionOntoZero)
{
  Vector v({3, 4});
  Vector u({0, 0});

  EXPECT_EQ(v.proj(u), u);
}

TEST(Vector, PlusReturnsVector)
{
  Vector u({0, 1});
  Vector v({2, 3});

  {
    auto nonConstU = u;
    nonConstU += v;

    EXPECT_EQ(nonConstU.getNCols(), 1);
    EXPECT_EQ(typeid(nonConstU), typeid(Vector));
  }

  {
    const auto constU = u;
    const auto uPlusV = constU + v;

    EXPECT_EQ(uPlusV.getNCols(), 1);
    EXPECT_EQ(typeid(uPlusV), typeid(Vector));
  }
}

TEST(Vector, MinusReturnsVector)
{
  Vector u({0, 1});
  Vector v({2, 3});

  {
    auto nonConstU = u;
    nonConstU -= v;

    EXPECT_EQ(nonConstU.getNCols(), 1);
    EXPECT_EQ(typeid(nonConstU), typeid(Vector));
  }

  {
    const auto constU = u;
    const auto uPlusV = constU - v;

    EXPECT_EQ(uPlusV.getNCols(), 1);
    EXPECT_EQ(typeid(uPlusV), typeid(Vector));
  }
}