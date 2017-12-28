#ifndef LS_CONSTANTS_H
#define LS_CONSTANTS_H

#include <cstdint>

typedef uint8_t ls_value_t;
#define LS_VALUE_RANGE 10

#define LS_ARRAY_SIZE 8

// (LS_ARRAY_SIZE+LS_VALUE_RANGE-1 choose LS_ARRAY_SIZE)
#define LS_NUM_ARRAYS 24310

#define LS_NOISE_STDDEV 1.0

#endif // LS_CONSTANT_H
