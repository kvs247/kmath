#include <kmath/Matrix/Matrix.hpp>
#include <kmath/Matrix/QR/GramSchmidtQR.hpp>
#include <kmath/Matrix/Vector.hpp>
#include <kmath/Utils.hpp>
#include <memory>
#include <utility>
#include <vector>

std::pair<Matrix, Matrix> GramSchmidtQR::decomp(const Matrix &m) const
{
  const auto colPtrs = m.getCols();
  auto firstCol = *colPtrs.front();
  std::vector<Vector> uVecs({firstCol});
  std::vector<Vector> newBasis({firstCol.normalize()});

  for (size_t i = 1; i < colPtrs.size(); ++i)
  {
    auto col = *colPtrs[i];
    const auto firstThisUVec = col - Vector(col).proj(uVecs.front());
    std::vector<Vector> thisUVecs({firstThisUVec});

    for (size_t k = 1; k < i; ++k)
    {
      const auto newThisUVec = thisUVecs.back() - Vector(thisUVecs.back()).proj(uVecs[k]);
      thisUVecs.push_back(newThisUVec);
    }

    uVecs.push_back(thisUVecs.back());
    newBasis.push_back(thisUVecs.back().normalize());
  }

  const auto q = Matrix(newBasis);
  const auto r = computeR(newBasis, colPtrs);

  return {q, r};
}

Matrix
GramSchmidtQR::computeR(const std::vector<Vector> &basis, const std::vector<std::shared_ptr<Vector>> &colPtrs) const
{
  const auto n = basis.size();
  std::vector<double> rData(n * n);
  for (size_t i = 0; i < n; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      if (j > i)
      {
        rData[i * n + j] = 0;
      }

      auto val = basis[i].innerProduct(*colPtrs[j]);
      if (kmath::floatEqual(val, 0.0))
      {
        val = 0.0;
      }
      rData[i * n + j] = val;
    }
  }
  return Matrix(rData, n, n);
}