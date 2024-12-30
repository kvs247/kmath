#include <kmath/Matrix/Vector.hpp>
#include <vector>

Vector::Vector(const std::vector<double> &eles) : Matrix(eles, eles.size(), 1) {}