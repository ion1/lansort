#ifndef LS_MEASURE_H
#define LS_MEASURE_H

#include <array>
#include <random>

#include "constants.h"

double measure(std::mt19937 &reng,
               const std::array<ls_value_t, LS_ARRAY_SIZE> &vals,
               const double sensor_stddev);

#endif // LS_MEASURE_H
