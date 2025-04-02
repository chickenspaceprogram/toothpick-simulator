#pragma once
#include <thread>
#include <iomanip>
#include <limits>
#include <array>
#include <thread>

#include "job.hpp"

inline void fillJobVector(std::vector<Job> &vec, std::size_t njobs, std::size_t batches_per_job) {
    for (std::size_t i = 0; i < njobs; ++i) {
        vec.push_back(std::move(Job(batches_per_job)));
    }
}

template <std::size_t num_threads>
void simulate_threads(std::ostream &out, std::size_t num_jobs, std::size_t batches_per_job, std::size_t batch_size) {
    out << std::setprecision(std::numeric_limits<double>::digits10 + 1);
    std::array<std::thread, num_threads> arr;
    std::array<std::vector<Job>, num_threads> jobs;
    for (std::size_t i = 0; i < num_jobs % num_threads; ++i) {
        fillJobVector(jobs[i], num_jobs / num_threads + 1, batches_per_job);
        arr[i] = std::thread(runJobs, std::ref(jobs[i]), batch_size);
    }

    for (std::size_t i = num_jobs % num_threads; i < num_threads; ++i) {
        fillJobVector(jobs[i], num_jobs / num_threads, batches_per_job);
        arr[i] = std::thread(runJobs, std::ref(jobs[i]), batch_size);
    }

    for (std::size_t i = 0; i < num_threads; ++i) {
        arr[i].join();
        for (const Job &job : jobs[i]) {
            job.print(out);
        }
    }
}
