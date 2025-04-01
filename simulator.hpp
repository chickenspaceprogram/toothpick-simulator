#pragma once

#include <cstdint>
#include <thread>
#include <array>
#include <iostream> 

std::uint64_t simulate(double toothpick_length, double length_between_lines, std::uint64_t num_trials);

inline void sim_return_val(std::uint64_t &return_val, double toothpick_length, double length_between_lines, std::uint64_t num_trials) {
    return_val = simulate(toothpick_length, length_between_lines, num_trials);
}

template <std::size_t NUM_THREADS>
std::uint64_t simulate_threads(double toothpick_length, double length_between_lines, std::uint64_t num_trials) {
    std::uint64_t trials_per_thread = num_trials / NUM_THREADS;
    std::size_t num_spare_trials = num_trials % NUM_THREADS;
    std::array<std::thread, NUM_THREADS> threads;
    std::array<std::uint64_t, NUM_THREADS> thread_results;
    std::uint64_t result = 0;

    for (std::size_t i = 0; i < num_spare_trials; ++i) {
        threads[i] = std::move(std::thread(sim_return_val, std::ref(thread_results[i]), toothpick_length, length_between_lines, trials_per_thread + 1));
    }
    for (std::size_t i = num_spare_trials; i < NUM_THREADS; ++i) {
        threads[i] = std::move(std::thread(sim_return_val, std::ref(thread_results[i]), toothpick_length, length_between_lines, trials_per_thread));
    }
    for (std::size_t i = 0; i < NUM_THREADS; ++i) {
        threads[i].join();
        result += thread_results[i];
    }
    return result;

}

inline void sim_batches(double toothpick_length, double length_between_lines, std::uint64_t num_batches, std::uint64_t trials_per_batch) {
    for (std::uint64_t i = 0; i < num_batches; ++i) {
        std::cout << simulate(toothpick_length, length_between_lines, trials_per_batch) << ",";
    }
    std::cout << std::endl;
}
