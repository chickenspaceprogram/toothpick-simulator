#pragma once
#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>
#include <ostream>
#include "simulator.hpp"

class Job {
    public:
    Job() = delete;
    Job(std::size_t num_batches) : arr(new double[num_batches]), num_batches(num_batches) {}
    Job(const Job &) = delete;
    Job &operator=(const Job &) = delete;
    Job(Job &&job) : arr(std::move(job.arr)), num_batches(job.num_batches) {}
    Job &operator=(Job &&job) {
        arr = std::move(job.arr);
        num_batches = job.num_batches;
        return *this;
    }

    double &operator[](std::size_t i) { return arr[i]; }
    const double &operator[](std::size_t i) const { return arr[i]; }
    void print(std::ostream &out) const {
        for (std::size_t i = 0; i < num_batches - 1; ++i) {
            out << arr[i] << ",";
        }
        out << arr[num_batches - 1] << std::endl;
    }
    void runJob(std::size_t batch_size) {
        for (std::size_t i = 0; i < num_batches; ++i) {
            arr[i] = (double)simulate(1, 1, batch_size) / batch_size;
        }
    }

    private:
    std::unique_ptr<double[]> arr;
    std::size_t num_batches;
};

inline void runJobs(std::vector<Job> &jobs, std::size_t batch_size) {
    for (Job &job : jobs) {
        job.runJob(batch_size);
    }
}

