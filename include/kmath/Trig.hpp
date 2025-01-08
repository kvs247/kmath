#pragma once

#include <utility>

namespace kmath
{
double reduceRad(double);
double reduceDeg(double);
double degToRad(double);
double radToDeg(double);

std::pair<double, double> polarToCart(double r, double t);
std::pair<double, double> cartToPolar(double x, double y);

double cos(double);
double sin(double);
double tan(double);
} // namespace kmath