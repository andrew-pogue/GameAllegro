#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>

// Wrapper for ALLEGRO_TIMER
struct Timer {
    Timer(double);
    ~Timer();

    operator ALLEGRO_TIMER*(void)
    { return timer_; }
private:
    ALLEGRO_TIMER* timer_;
};