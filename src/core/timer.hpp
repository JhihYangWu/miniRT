#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using clk = std::chrono::high_resolution_clock;

class Timer{
public:
    // constructor
    Timer();
    
    // methods
    void reset();
    unsigned int getElapsedTime(); // returns ms since constructed or resetted
    
    // attributes
    std::chrono::time_point<clk> tik;
};

#endif
