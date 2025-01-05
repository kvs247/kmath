#include <gtest/gtest.h>
#include <kmath/Matrix/Matrix.hpp>
#include <kmath/Matrix/QR/GramSchmidtQR.hpp>
#include <stdexcept>

TEST(GramSchmidtQR, Snapshot)
{
  GramSchmidtQR qr;

  Matrix m({{12, -51, 4}, {6, 167, -68}, {-4, 24, -41}});

  Matrix expectedQ(
      {{6.0 / 7, -69.0 / 175, -58.0 / 175}, {3.0 / 7, 158.0 / 175, 6.0 / 175}, {-2.0 / 7, 6.0 / 35, -33.0 / 35}});
  Matrix expectedR({{14, 21, -14}, {0, 175, -70}, {0, 0, 35}});

  const auto res = qr.decomp(m);
  const auto q = res.first;
  const auto r = res.second;

  EXPECT_EQ(q, expectedQ);
  EXPECT_EQ(r, expectedR);
}