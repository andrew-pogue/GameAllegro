#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include "alcpp_init.hpp"

// Wrapper for ALLEGRO_TIMER
struct Timer : Init {
    Timer(double);
    ~Timer();

    operator ALLEGRO_TIMER*(void)
    { return timer_; }
private:
    ALLEGRO_TIMER* timer_;
};