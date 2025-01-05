namespace kmath
{
constexpr double DEFAULT_FLOAT_RELATIVE_TOLERANCE = 1e-12;

bool floatEqual(const double a, const double b, const double relTol = DEFAULT_FLOAT_RELATIVE_TOLERANCE);
} // namespace kmath