#pragma once
#include <allegro5/allegro.h>
#include <stdio.h>

/**
 * Wrapper for ALLEGRO_DISPLAY
 **/
struct Display {
    Display(int, int);
    ~Display();

    int get_height() const;
    int get_width() const;
    
    operator ALLEGRO_DISPLAY* ()
    { return display_; }
    
    operator ALLEGRO_EVENT_SOURCE* ()
    { return al_get_display_event_source(display_); }
private:
    ALLEGRO_DISPLAY* display_;
}; // struct Display