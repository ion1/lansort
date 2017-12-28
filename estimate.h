#ifndef LS_ESTIMATE_H
#define LS_ESTIMATE_H

#include <array>
#include <iostream>
#include <tuple>

#include "constants.h"

class Candidate {
public:
  std::array<ls_value_t, LS_ARRAY_SIZE> values;
  double log_p;

  friend std::ostream &operator<<(std::ostream &out,
                                  const Candidate &candidate);
};

class Estimate {
public:
  std::array<Candidate, LS_NUM_ARRAYS> candidates;

  Estimate(void);

  void add_measurement(const double val, const double stddev);

  const std::tuple<Candidate, Candidate> best_candidates(void);

  friend std::ostream &operator<<(std::ostream &out, const Estimate &estimate);

private:
  void normalize(void);
};

#endif // LS_ESTIMATE_H
