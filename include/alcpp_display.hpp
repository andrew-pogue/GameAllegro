#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include "alcpp_init.hpp"

// Wrapper for ALLEGRO_DISPLAY
struct Display : Init {
    // Assumes that the Allegro core library was already initialized.
    Display(int, int, int, int, int);
    ~Display();

    operator ALLEGRO_DISPLAY*(void)
    { return display_; }

    int get_height() const
    { return height_; }

    int get_width() const
    { return width_; }

    int x, y, z; // position in game world
private:
    ALLEGRO_DISPLAY* display_;
    int width_;
    int height_;
};