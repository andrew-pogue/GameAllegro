#include "al_display.hpp"

static const bool DEBUG = true;

Display::Display(int width, int height)
    : display_(nullptr)
{
    if (DEBUG) printf("Display::Display(%i, %i)\n", width, height);
    display_ = al_create_display(width, height);
    if (!display_) throw "Error: failed to create display.";
}

Display::~Display() {
    if (DEBUG) printf("Display::~Display()\n");
    al_destroy_display(display_);
}

int Display::get_height() const { return al_get_display_height(display_); }
int Display::get_width() const { return al_get_display_width(display_); }