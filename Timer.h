#ifndef AIZO_TIMER_H
#define AIZO_TIMER_H
#include <chrono>

// Measures time
class Timer {
public:
    Timer();
    void reset();
    int start();
    int stop();
    int result();
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
};


#endif //AIZO_TIMER_H
