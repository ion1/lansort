#include <array>
#include <fstream>
#include <iostream>
#include <random>

#include "constants.h"
#include "estimate.h"
#include "measure.h"

int main(void) {
  static_assert(sizeof(Estimate) <= 500000000,
                "Memory consumption is reasonable");
  std::cout << "Memory usage: " << ((double)sizeof(Estimate) / 1000000.0)
            << " MB\n";

  std::random_device rdev;
  std::mt19937 reng(rdev());

  std::array<ls_value_t, LS_ARRAY_SIZE> vals = {0, 0, 2, 3, 4, 4, 4, 8};

  std::ofstream measurements_log("measurements.dat");

  auto est = Estimate();

  for (int i = 0;; ++i) {
    auto m = measure(reng, vals, LS_NOISE_STDDEV);
    measurements_log << m << "\n";
    est.add_measurement(m, LS_NOISE_STDDEV);

    auto best = est.best_candidates();

    std::cout << "iteration=" << i << " measurement=" << m
              << " best=" << std::get<0>(best) << "\n";

    if (std::get<0>(best).log_p - std::get<1>(best).log_p >= 24) {
      break;
    }
  }

  // std::cout << est;

  auto best = est.best_candidates();

  std::cout << "Best:   " << std::get<0>(best) << "\n";
  std::cout << "Second: " << std::get<1>(best) << "\n";

  return 0;
}
