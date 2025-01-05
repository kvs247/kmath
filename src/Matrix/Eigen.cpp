#include <kmath/Matrix/Eigen.hpp>
#include <kmath/Matrix/QR/GramSchmidtQR.hpp>
#include <kmath/Matrix/Vector.hpp>
#include <kmath/Utils.hpp>
#include <map>
#include <vector>

std::map<double, std::vector<Vector>> Eigen::compute(Matrix m)
{
  static GramSchmidtQR qr;

  const int ITERATIONS = 200;

  Matrix u = Matrix::makeIdentityMatrix(m.getNCols());
  Matrix lastM = m;

  for (size_t k = 0; k < ITERATIONS; ++k)
  {
    const auto qrDecomp = qr.decomp(m);
    const auto q = qrDecomp.first;
    const auto r = qrDecomp.second;

    lastM = m;
    m = r * q;
    u *= q;
  }

  auto orderedEigenVals = m.getDiagonal();
  const auto orderedEigenVectors = u.getCols();

  if (orderedEigenVals.size() != orderedEigenVectors.size())
  {
    throw std::runtime_error("orderedEigenVals and orderedEigenVectos have unequal size");
  }

  for (size_t i = 1; i < orderedEigenVals.size(); ++i)
  {
    for (size_t j = 0; j < i; ++j)
    {
      if (kmath::floatEqual(orderedEigenVals[i], orderedEigenVals[j]))
      {
        orderedEigenVals[i] = orderedEigenVals[j];
        break;
      }
    }
  }

  std::map<double, std::vector<Vector>> res;
  for (size_t i = 0; i < orderedEigenVals.size(); ++i)
  {
    auto &entry = res[orderedEigenVals[i]];
    entry.push_back(*orderedEigenVectors[i]);
  }
  return res;
}