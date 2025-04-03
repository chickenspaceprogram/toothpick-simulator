#include <random>
#include <cmath>
#include "simulator.hpp"
#include "pcg/pcg_random.hpp"

// this code isn't the greatest but it does work
// It should also be easily parallelizable, at least on the CPU.
// I haven't messed with GPU programming before to be honest and I wanted to finish this relatively quickly.

struct Point {
    Point() = delete;
    Point (pcg32 &gen) {
        std::uniform_real_distribution<double> x_dist(-1, 1);
        std::uniform_real_distribution<double> y_dist(0, 1);

        do {
            x = x_dist(gen);
            y = y_dist(gen);
        } while (x * x + y * y > 1);
    }
    inline double getHeight(double length) const {
        return (y * length) / std::sqrt(x * x + y * y);
    }
    double x;
    double y;
};

inline double randHeight(pcg32 &gen, double length) {
    std::uniform_real_distribution<double> dist(0, length);
    return dist(gen);
}

inline std::uint64_t sim_trial(pcg32 &gen, double toothpick_length, double length_between_lines) {
    Point pt(gen);
    if (randHeight(gen, length_between_lines) + pt.getHeight(toothpick_length) < length_between_lines) {
        return 0;
    }
    return 1;
}

std::uint64_t simulate(double toothpick_length, double length_between_lines, std::uint64_t num_trials) {
    pcg32 rand(pcg_extras::seed_seq_from<std::random_device>{});
    std::uint64_t result = 0;
    for (std::uint64_t i = 0; i < num_trials; ++i) {
        result += sim_trial(rand, toothpick_length, length_between_lines);
    }
    return result;
}

