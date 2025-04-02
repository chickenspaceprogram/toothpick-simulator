#include <iostream>
#include "threads.hpp"

constexpr std::size_t NUM_JOBS = 10;
constexpr std::size_t BATCHES_PER_JOB = 20;
constexpr std::size_t BATCH_SIZE = 1000;
constexpr std::size_t NUM_THREADS = 8;

int main(void) {
    std::cerr << "Number of jobs: " << NUM_JOBS << std::endl
              << "Number of batches per job: " << BATCHES_PER_JOB << std::endl
              << "Simulations per batch: " << BATCH_SIZE << std::endl
              << "Simulations per job: " << BATCH_SIZE * BATCHES_PER_JOB << std::endl
              << "Number of threads: " << NUM_THREADS << std::endl << std::endl;
    simulate_threads<NUM_THREADS>(std::cout, NUM_JOBS, BATCHES_PER_JOB, BATCH_SIZE);
}
