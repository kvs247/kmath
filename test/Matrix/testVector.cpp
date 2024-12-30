#include <gtest/gtest.h>
#include <kmath/Matrix/Vector.hpp>
#include <stdexcept>

// constructors
TEST(Vector, CanCreateVector)
{
  Vector v({1, 2, 3, 4});

  size_t expectedNRows = 4;
  size_t expectedNCols = 1;
  std::vector<double> expectedData{1, 2, 3, 4};

  EXPECT_EQ(v.getNRows(), expectedNRows);
  EXPECT_EQ(v.getNCols(), expectedNCols);
}
