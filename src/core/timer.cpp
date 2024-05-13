#include "timer.hpp"

Timer::Timer() {
    tik = clk::now();
}

void Timer::reset() {
    tik = clk::now();
}

unsigned int Timer::getElapsedTime() {
    std::chrono::time_point<clk> tok = clk::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(tok - tik).count();
}
