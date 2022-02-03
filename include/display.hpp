#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>

// Wrapper for ALLEGRO_DISPLAY
struct Display {
    // Assumes that the Allegro core library was already initialized.
    Display(int, int, int, int, int);
    ~Display();

    operator ALLEGRO_DISPLAY*(void)
    { return display_; }
private:
    ALLEGRO_DISPLAY* display_;
    int width_;
    int height_;
    int x_, y_, z_;
};