#include "alcpp_display.hpp"

static const bool DEBUG = true;

Display::Display(int width, int height, int x, int y, int z)
    : x(x), y(y), z(z), display_(nullptr), width_(width), height_(height)
{
    if (DEBUG) printf("Display::Display(%i, %i, %i, %i, %i)\n", width, height, x, y, z);
    display_ = al_create_display(width, height);
    if (!display_) throw "Error: failed to create display.";
}

Display::~Display() {
    if (DEBUG) printf("Display::~Display()\n");
    al_destroy_display(display_);
}