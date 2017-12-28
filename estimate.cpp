#include <cmath>
#include <iostream>
#include <iterator>

#include "constants.h"
#include "estimate.h"

static constexpr double gaussian_coeff(void) {
  // pi = 4 * atan(1)
  return 1.0 / sqrt(2 * 4 * atan(1));
}

static double gaussian(const double mean, const double measurement,
                       const double stddev) {
  double diff = measurement - mean;
  return exp(-diff * diff / (2 * stddev * stddev)) * gaussian_coeff() / stddev;
}

static void
next_candidate(const std::array<ls_value_t, LS_ARRAY_SIZE> &previous,
               std::array<ls_value_t, LS_ARRAY_SIZE> &next) {
  for (int i = 0; i < LS_ARRAY_SIZE; ++i) {
    next[i] = previous[i];
  }

  // Increment the last value that can be incremented without an overflow.
  int i = LS_ARRAY_SIZE - 1;
  for (;; --i) {
    ++next[i];
    if (next[i] < LS_VALUE_RANGE) {
      break;
    }
    if (i == 0) {
      throw std::runtime_error("next_candidate: overflow");
    }
  }
  // Set the final values to match the one that was incremented.
  for (++i; i < LS_ARRAY_SIZE; ++i) {
    next[i] = next[i - 1];
  }
}

Estimate::Estimate(void) {
  for (auto &val : candidates[0].values) {
    val = 0;
  }
  candidates[0].log_p = 0.0;

  for (int i = 1; i < LS_NUM_ARRAYS; ++i) {
    next_candidate(candidates[i - 1].values, candidates[i].values);
    candidates[i].log_p = 0.0;
  }

  normalize();
}

void Estimate::add_measurement(const double val, const double stddev) {
  for (auto &candidate : candidates) {
    double probability = 0.0;
    for (auto candidate_val : candidate.values) {
      probability += gaussian((double)candidate_val, val, stddev);
    }
    candidate.log_p += log(probability);
  }

  normalize();
}

const std::tuple<Candidate, Candidate> Estimate::best_candidates(void) {
  auto *best = &candidates[0];
  auto *second_best = &candidates[0];

  for (auto &candidate : candidates) {
    if (candidate.log_p > best->log_p) {
      second_best = best;
      best = &candidate;
    }
  }

  return std::make_tuple(*best, *second_best);
}

void Estimate::normalize(void) {
  double sum = 0.0;

  for (auto &candidate : candidates) {
    sum += exp(candidate.log_p);
  }

  double log_sum = log(sum);

  for (auto &candidate : candidates) {
    candidate.log_p -= log_sum;
  }
}

std::ostream &operator<<(std::ostream &out, const Candidate &candidate) {
  out << "Candidate{{";
  std::copy(candidate.values.begin(), candidate.values.end(),
            std::ostream_iterator<int>(out, ","));
  out << "}," << candidate.log_p << "}";

  return out;
}

std::ostream &operator<<(std::ostream &out, const Estimate &estimate) {
  out << "Estimate:\n";
  std::copy(estimate.candidates.begin(), estimate.candidates.end(),
            std::ostream_iterator<Candidate>(out, "\n"));
  out << "\n";

  return out;
}
