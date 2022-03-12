#pragma once
#include <allegro5/allegro.h>
#include <stdio.h>

/**
 * Wrapper for ALLEGRO_DISPLAY
 **/
struct Display {
    Display(int width, int height) : display_(nullptr) {
        display_ = al_create_display(width, height);
        if (!display_) throw "Error: failed to create display.";
    }

    ~Display() {
        al_destroy_display(display_);
    }

    int get_height() const { return al_get_display_height(display_); }
    int get_width() const { return al_get_display_width(display_); }
    
    operator ALLEGRO_DISPLAY* ()
    { return display_; }
    
    operator ALLEGRO_EVENT_SOURCE* ()
    { return al_get_display_event_source(display_); }
private:
    ALLEGRO_DISPLAY* display_;
};