#include <kmath/Matrix/Eigen.hpp>
#include <kmath/Matrix/QR/GramSchmidtQR.hpp>
#include <kmath/Matrix/Vector.hpp>
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

  auto newData = m.getData();
  auto lastMData = lastM.getData();
  for (size_t i = 0; i < newData.size(); ++i)
  {
    if (lastMData[i] == 0)
    {
      continue;
    }
    newData[i] /= lastMData[i];
  }
  const Matrix lastTwoRatio(newData, m.getNRows(), m.getNCols());
  std::cout << "===\n";
  lastTwoRatio.print();

  const auto orderedEigenVals = lastTwoRatio.getDiagonal();
  const auto orderedEigenVectors = u.getCols();

  if (orderedEigenVals.size() != orderedEigenVectors.size())
  {
    throw std::runtime_error("orderedEigenVals and orderedEigenVectos have unequal size");
  }

  std::map<double, std::vector<Vector>> res;
  for (size_t i = 0; i < orderedEigenVals.size(); ++i)
  {
    auto &entry = res[orderedEigenVals[i]];
    entry.push_back(*orderedEigenVectors[i]);
  }
  return res;
}