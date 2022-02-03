#include "display.hpp"

static const bool DEBUG = false;

Display::Display(int width, int height, int x, int y, int z)
    : width_(width), height_(height), x_(x), y_(y), z_(z)
{
    if (DEBUG) printf("Display::Display(%u, %u, %i, %i, %i)\n", width, height, x, y, z);
    display_ = al_create_display(width, height);
    if (!display_) throw "Error: failed to create display.";
}

Display::~Display() {
    if (DEBUG) printf("Display::~Display()\n");
    al_destroy_display(display_);
}