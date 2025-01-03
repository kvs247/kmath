#pragma once

#include <kmath/Matrix/Matrix.hpp>
#include <kmath/Matrix/Vector.hpp>
#include <map>
#include <utility>
#include <vector>

class Eigen
{
public:
  static std::map<double, std::vector<Vector>> compute(Matrix);
};