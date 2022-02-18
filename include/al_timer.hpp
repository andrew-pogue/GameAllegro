#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>

// Wrapper for ALLEGRO_TIMER
struct Timer {
    Timer(double);
    ~Timer();

    void start();
    void stop();
    void resume();

    operator ALLEGRO_TIMER*()
    { return timer_; }

    operator ALLEGRO_EVENT_SOURCE*()
    { return al_get_timer_event_source(timer_); }
private:
    ALLEGRO_TIMER* timer_;
};