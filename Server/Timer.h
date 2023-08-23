#pragma once
#include <iostream>
#include <chrono>

class Timer {
public:
    void Start() {
        start_time_ = std::chrono::high_resolution_clock::now();
    }

    void Stop() {
        end_time_ = std::chrono::high_resolution_clock::now();
    }

    auto ShowResult() const {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time_ - start_time_).count();
        return duration; 
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time_;
};


