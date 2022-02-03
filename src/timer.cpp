#include "timer.hpp"

static const bool DEBUG = false;

Timer::Timer(double seconds) {
    if (DEBUG) printf("Timer::Timer()");
    timer_ = al_create_timer(seconds);
    if (!timer_) throw "Error: failed to create timer.";
}

Timer::~Timer() {
    if (DEBUG) printf("Timer::~Timer()");
    al_destroy_timer(timer_);
}