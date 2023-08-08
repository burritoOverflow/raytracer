#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

const size_t PROGRESS_BAR_WIDTH = 80;

class ProgressBar {
public:
    explicit ProgressBar(size_t total_iterations) : total_iterations_(total_iterations) {}

    void Update(size_t current_iteration) {
        if (current_iteration > current_iteration_) {
            current_iteration_ = current_iteration;
        }
    }

    void Print() const {
        size_t percentage =
                (current_iteration_ * PROGRESS_BAR_WIDTH) / total_iterations_;

        const auto now = std::chrono::high_resolution_clock::now();
        const auto minutes =
                std::chrono::duration_cast<std::chrono::minutes>(now - start_time_);
        const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(
                now - start_time_ - minutes);

        std::stringstream time;
        time << " | " << std::setw(2) << std::setfill('0') << minutes.count() << ":"
             << std::setw(2) << std::setfill('0') << seconds.count();

        std::string progress =
                "\r[" + std::string(percentage, '=') + ">" +
                std::string((PROGRESS_BAR_WIDTH - 1) - percentage, ' ') + "] " +
                std::to_string(current_iteration_) + "/" +
                std::to_string(total_iterations_);

        progress += time.str();
        std::cout << progress << std::flush;
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_ =
            std::chrono::high_resolution_clock::now();
    size_t current_iteration_ = 0;
    size_t total_iterations_ = 0;
};
