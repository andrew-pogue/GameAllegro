#include "alcpp_display.hpp"

static const bool DEBUG = true;

Display::Display(int width, int height)
    : follow_x_(nullptr), follow_y_(nullptr), follow_z_(nullptr), display_(nullptr),
    width_(width), height_(height)
{
    if (DEBUG) printf("Display::Display(%i, %i)\n", width, height);
    display_ = al_create_display(width, height);
    if (!display_) throw "Error: failed to create display.";
}

Display::~Display() {
    if (DEBUG) printf("Display::~Display()\n");
    al_destroy_display(display_);
}