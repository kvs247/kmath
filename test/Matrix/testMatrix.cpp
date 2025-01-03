#include <gtest/gtest.h>
#include <kmath/Matrix/Matrix.hpp>
#include <kmath/Matrix/Vector.hpp>
#include <stdexcept>
#include <vector>

// constructors
TEST(Matrix, CanCreateMatrixFromCols)
{
  std::vector<Vector> cols = {
      Vector({1, 2}),
      Vector({4, 5}),
      Vector({7, 8}),
  };

  const size_t expectedNCols = 3;
  const size_t expectedNRows = 2;
  const std::vector<double> expectedData{1, 4, 7, 2, 5, 8};

  const auto m = Matrix(cols);

  EXPECT_EQ(m.getNRows(), expectedNRows);
  EXPECT_EQ(m.getNCols(), expectedNCols);
  EXPECT_EQ(m.getData(), expectedData);
}

TEST(Matrix, CanCreateMatrixFromRows)
{
  Matrix m({{1, 2}, {3, 4}, {5, 6}});

  const size_t expectedNCols = 2;
  const size_t expectedNRows = 3;
  const std::vector<double> expectedData{1, 2, 3, 4, 5, 6};

  EXPECT_EQ(m.getNRows(), expectedNRows);
  EXPECT_EQ(m.getNCols(), expectedNCols);
  EXPECT_EQ(m.getData(), expectedData);
}

TEST(Matrix, CanCreateMatrixFromDataAndShape)
{
  Matrix m({1, 2, 3, 4, 5, 6}, 3, 2);

  std::vector<Vector> expectedRows = {
      Vector({1, 2}),
      Vector({3, 4}),
      Vector({5, 6}),
  };

  std::vector<Vector> expectedCols = {
      Vector({1, 3, 5}),
      Vector({2, 4, 6}),
  };

  auto actualRows = m.getRows();
  auto actualCols = m.getCols();

  EXPECT_EQ(m.getNRows(), expectedRows.size());
  for (size_t i = 0; i < expectedRows.size(); ++i)
  {
    EXPECT_EQ(*actualRows[i], expectedRows[i]);
  }

  EXPECT_EQ(m.getNCols(), expectedCols.size());
  for (size_t i = 0; i < expectedCols.size(); ++i)
  {
    EXPECT_EQ(*actualCols[i], expectedCols[i]);
  }
}

TEST(Matrix, ThrowOnCreateInvalidMatrix) { EXPECT_THROW(Matrix m({{1, 2}, {3, 4, 5}}), std::invalid_argument); }

TEST(Matrix, ThrowsOnCreateInvalidMatrix1D) { EXPECT_THROW(Matrix m({1, 2, 3, 4, 5}, 3, 2), std::invalid_argument); }

// getters
TEST(Matrix, GetNRows)
{
  Matrix m({{1, 2}, {3, 4}, {5, 6}});

  EXPECT_EQ(m.getNRows(), 3);
}

TEST(Matrix, GetNCols)
{
  Matrix m({{1, 2}, {3, 4}, {5, 6}});

  EXPECT_EQ(m.getNCols(), 2);
}

TEST(Matrix, GetRows)
{
  Matrix m({{1, 2}, {3, 4}, {5, 6}});

  const std::vector<Vector> expectedRows = {
      Vector({1, 2}),
      Vector({3, 4}),
      Vector({5, 6}),
  };
  const auto actualRows = m.getRows();

  EXPECT_EQ(m.getNRows(), expectedRows.size());
  for (size_t i = 0; i < expectedRows.size(); ++i)
  {
    EXPECT_EQ(*actualRows[i], expectedRows[i]);
  }
}

TEST(Matrix, GetCols)
{
  Matrix m({{1, 2}, {3, 4}, {5, 6}});

  const std::vector<Vector> expectedCols = {
      Vector({1, 3, 5}),
      Vector({2, 4, 6}),
  };
  const auto actualCols = m.getCols();

  EXPECT_EQ(m.getNCols(), expectedCols.size());
  for (size_t i = 0; i < expectedCols.size(); ++i)
  {
    EXPECT_EQ(*actualCols[i], expectedCols[i]);
  }
}

TEST(Matrix, GetData)
{
  Matrix m({{1, 2}, {3, 4}, {5, 6}});

  std::vector<double> expectedData{1, 2, 3, 4, 5, 6};

  EXPECT_EQ(m.getData(), expectedData);
}

TEST(Matrix, GetDiagonal)
{
  Matrix m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

  const std::vector<double> expected{1, 5, 9};

  EXPECT_EQ(m.getDiagonal(), expected);
}

TEST(Matrix, GetDiagonalNonSquareMatrix)
{
  Matrix m({{1, 2, 3}, {4, 5, 6}});

  EXPECT_THROW(m.getDiagonal(), std::invalid_argument);
}

// public methods
TEST(Matrix, IsSquare)
{
  Matrix m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  Matrix m2({{1, 2, 3}, {4, 5, 6}});

  EXPECT_TRUE(m1.isSquare());

  EXPECT_FALSE(m2.isSquare());
}

TEST(Matrix, IsSameDimension)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{0, 1}, {1, 0}, {0, 1}});
  Matrix m3({{1, 0}, {0, 1}});

  EXPECT_TRUE(Matrix::isSameDimension(m1, m2));
  EXPECT_FALSE(Matrix::isSameDimension(m1, m3));
  EXPECT_FALSE(Matrix::isSameDimension(m2, m3));
}

TEST(Matrix, MakeIdentityMatrix)
{
  size_t dim = 4;

  Matrix expected({{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});

  EXPECT_EQ(Matrix::makeIdentityMatrix(dim), expected);
}

TEST(Matrix, AtWithValidInput)
{
  Matrix m({{1, 2}, {3, 4}, {5, 6}});

  EXPECT_EQ(m.at(0, 0), 1);
  EXPECT_EQ(m.at(1, 0), 3);
  EXPECT_EQ(m.at(2, 0), 5);
  EXPECT_EQ(m.at(0, 1), 2);
  EXPECT_EQ(m.at(1, 1), 4);
  EXPECT_EQ(m.at(2, 1), 6);
}

TEST(Matrix, AtWithInvalidInput)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});

  EXPECT_THROW(m1.at(0, 2), std::out_of_range);
  EXPECT_THROW(m1.at(3, 0), std::out_of_range);
}

TEST(Matrix, Transpose)
{
  Matrix m({{1, 2, 3}, {4, 5, 6}});
  Matrix mt({{1, 4}, {2, 5}, {3, 6}});

  {
    auto mNonConst = m;

    EXPECT_EQ(mNonConst.transpose(), mt);
    EXPECT_NE(mNonConst, m);
  }

  {
    const auto mConst = m;
    auto mTranspose = mConst.transpose();

    EXPECT_EQ(mTranspose, mt);
    EXPECT_EQ(mConst, m);
  }
}

// operators
TEST(Matrix, Assignment)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{1, 2, 3}, {4, 5, 6}});

  m1 = m2;

  EXPECT_TRUE(m1 == m2);
}

TEST(Matrix, MatrixEquality)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{1, 2}, {3, 4}, {5, 6}});
  Matrix m3({{1, 0}, {0, 1}});
  Matrix m4({{1, 2, 3}, {4, 5, 6}});

  EXPECT_TRUE(m1 == m2);
  EXPECT_FALSE(m1 == m3);
  EXPECT_FALSE(m1 == m4);
}

TEST(Matrix, MatrixInequality)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{1, 2}, {3, 4}, {5, 6}});
  Matrix m3({{1, 0}, {0, 1}});
  Matrix m4({{1, 2, 3}, {4, 5, 6}});

  EXPECT_FALSE(m1 != m2);
  EXPECT_TRUE(m1 != m3);
  EXPECT_TRUE(m1 != m4);
}

TEST(Matrix, CanPlusEqualTwoMatrices)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{1, 0}, {-2, 3}, {0, -9}});

  Matrix expectedMatrix({{2, 2}, {1, 7}, {5, -3}});

  m1 += m2;
  EXPECT_EQ(m1, expectedMatrix);
}

TEST(Matrix, CannotPlusEqualUnequalDimensionMatrices)
{
  Matrix m1({{0, 1}, {1, 0}, {0, 1}});
  Matrix m2({{1, 0}, {0, 1}});

  EXPECT_THROW(m1 += m2, std::invalid_argument);
}

TEST(Matrix, CanAddTwoMatrices)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{1, 0}, {-2, 3}, {0, -9}});

  Matrix expectedMatrix({{2, 2}, {1, 7}, {5, -3}});

  EXPECT_EQ(m1 + m2, expectedMatrix);
}

TEST(Matrix, CannotAddUnequalDimensionMatrices)
{
  Matrix m1({{0, 1}, {1, 0}, {0, 1}});
  Matrix m2({{1, 0}, {0, 1}});

  EXPECT_THROW(m1 + m2, std::invalid_argument);
}

TEST(Matrix, CanMinusEqualTwoMatrices)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{1, 0}, {-2, 3}, {0, -9}});

  Matrix expectedMatrix({{0, 2}, {5, 1}, {5, 15}});

  m1 -= m2;
  EXPECT_EQ(m1, expectedMatrix);
}

TEST(Matrix, CannotMinusEqualUnequalDimensionMatrices)
{
  Matrix m1({{0, 1}, {1, 0}, {0, 1}});
  Matrix m2({{1, 0}, {0, 1}});

  EXPECT_THROW(m1 -= m2, std::invalid_argument);
}

TEST(Matrix, CanSubtractTwoMatrices)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{1, 0}, {-2, 3}, {0, -9}});

  Matrix expectedMatrix({{0, 2}, {5, 1}, {5, 15}});

  EXPECT_EQ(m1 - m2, expectedMatrix);
}

TEST(Matrix, CannotSubtractUnequalDimensionMatrices)
{
  Matrix m1({{0, 1}, {1, 0}, {0, 1}});
  Matrix m2({{1, 0}, {0, 1}});

  EXPECT_THROW(m1 - m2, std::invalid_argument);
}

TEST(Matrix, CanStarEqualTwoMatrices)
{
  Matrix m1({{1, 2, 3}, {4, 5, 6}});
  Matrix m2({{0, 1, 1}, {2, 3, 5}, {8, 13, 21}});

  Matrix expectedMatrix({{28, 46, 74}, {58, 97, 155}});

  m1 *= m2;
  EXPECT_EQ(m1, expectedMatrix);
}

TEST(Matrix, CannotStarEqualInvalidMatrixDimensions)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{0, 1, 1}, {2, 3, 5}, {8, 13, 21}});

  EXPECT_THROW(m1 *= m2, std::invalid_argument);
}

TEST(Matrix, CanMultiplyTwoMatrices)
{
  Matrix m1({{1, 2, 3}, {4, 5, 6}});
  Matrix m2({{0, 1, 1}, {2, 3, 5}, {8, 13, 21}});

  Matrix expectedMatrix({{28, 46, 74}, {58, 97, 155}});

  EXPECT_EQ(m1 * m2, expectedMatrix);
}

TEST(Matrix, CannotMultiplyInvalidMatrixDimensions)
{
  Matrix m1({{1, 2}, {3, 4}, {5, 6}});
  Matrix m2({{0, 1, 1}, {2, 3, 5}, {8, 13, 21}});

  EXPECT_THROW(m1 * m2, std::invalid_argument);
}