#include <gtest/gtest.h>
#include <kmath/Matrix/Eigen.hpp>
#include <kmath/Ops.hpp>

TEST(Eigen, Snapshot)
{
  // Matrix m({
  //     {2, 0, -1, -1, 0},
  //     {0, 0, 0, 0, 0},
  //     {-1, 0, 1, 0, 0},
  //     {-1, 0, 0, 1, 0},
  //     {0, 0, 0, 0, 0},
  // });

  Matrix m({
      {1, -1, 0},
      {-1, 2, -1},
      {0, -1, 1},
  });

  m.print();

  const auto result = Eigen::compute(m);

  for (const auto &eigenMapItem : result)
  {
    const auto eVal = eigenMapItem.first;
    const auto eVecs = eigenMapItem.second;

    std::cout << "λ = " << eVal << "\n";
    for (const auto &v : eVecs)
    {
      std::cout << "\t[ ";
      for (size_t i = 0; i < v.size(); ++i)
      {
        std::cout << v.at(i) << " ";
      }
      std::cout << "]\n";
    }
  }
}

TEST(Eigen, GroupsEigenValuesWithinTolerance)
{
  Matrix m({
      {2, -1, -1},
      {-1, 2, -1},
      {-1, -1, 2},
  });

  const std::vector<double> expected = {0.0, 3.0};

  const auto result = Eigen::compute(m);

  EXPECT_EQ(result.size(), expected.size());

  size_t i = 0;
  for (const auto &eValVec : result)
  {
    EXPECT_TRUE(kmath::abs(eValVec.first - expected[i++]) < 1e-10);
  }
}