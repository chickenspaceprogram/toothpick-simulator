#include "simulator.hpp"
#include <iostream>

constexpr std::uint64_t NUM_SIMS = 10000000000;
constexpr std::size_t NUM_THREADS = 8;

int main(void) {
    std::cout << (double)2 * NUM_SIMS / simulate_threads<NUM_THREADS>(1, 1, NUM_SIMS) << std::endl;
}
