#include "al_timer.hpp"

static const bool DEBUG = true;

Timer::Timer(double seconds) 
    : timer_(nullptr)
{
    if (DEBUG) printf("Timer::Timer(%f)\n", seconds);
    timer_ = al_create_timer(seconds);
    if (!timer_) throw "Error: failed to create timer.";
}

Timer::~Timer() {
    if (DEBUG) printf("Timer::~Timer()\n");
    al_destroy_timer(timer_);
}

void Timer::start() {
    al_start_timer(timer_);
}

void Timer::stop() {
    al_stop_timer(timer_);
}

void Timer::resume() {
    al_resume_timer(timer_);
}