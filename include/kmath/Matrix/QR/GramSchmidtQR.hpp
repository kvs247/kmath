#pragma once

#include "QRDecomposition.hpp"

class GramSchmidtQR : public QRDecomposition
{
public:
  std::pair<Matrix, Matrix> decomp(const Matrix &) const override;

private:
  Matrix computeR(const std::vector<Vector> &basis, const std::vector<std::shared_ptr<Vector>> &colPtrs) const;
};