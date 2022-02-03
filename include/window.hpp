#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>

struct Window {
    // Assumes that the Allegro core library was already initialized.
    Window(unsigned short, unsigned short, int, int, int);
    ~Window();
private:
    ALLEGRO_DISPLAY* display_;
    unsigned short width_;
    unsigned short height_;
    int x_, y_, z_;
};