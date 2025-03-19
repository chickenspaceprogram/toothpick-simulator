#include "simulator.hpp"
#include <iostream>
#include <iomanip>
#include <limits>

constexpr std::uint64_t NUM_SIMS = 10'000'000'000;
constexpr std::size_t NUM_THREADS = 40;

int main(void) {
    std::cout << std::setprecision(std::numeric_limits<double>::digits10 + 1)
              << "Precision is currently: " << std::numeric_limits<double>::digits10 << std::endl
              << "Number of simulations: " << NUM_SIMS << std::endl
              << "Number of threads: " << NUM_THREADS << std::endl << std::endl
              << "Estimation for pi: " << (double)2 * NUM_SIMS / simulate_threads<NUM_THREADS>(1, 1, NUM_SIMS) << std::endl;
}
