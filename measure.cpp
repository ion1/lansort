#include <array>
#include <random>

#include "constants.h"

double measure(std::mt19937 &reng,
               const std::array<ls_value_t, LS_ARRAY_SIZE> &vals,
               const double sensor_stddev) {
  std::uniform_int_distribution<int> uniform_dist(0, vals.size() - 1);

  std::size_t n = uniform_dist(reng);
  ls_value_t val = vals.at(n);

  std::normal_distribution<double> measurement{(double)val, sensor_stddev};

  return measurement(reng);
}
