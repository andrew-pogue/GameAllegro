#include "window.hpp"

static const bool DEBUG = false;

Window::Window(unsigned short width, unsigned short height, int x, int y, int z)
    : width_(width), height_(height), x_(x), y_(y), z_(z)
{
    if (DEBUG) printf("Window::Window(%u, %u, %i, %i, %i)\n", width, height, x, y, z);
    display_ = al_create_display(width, height);
    if (!display_) throw "Error: failed to create display.";
}

Window::~Window() {
    if (DEBUG) printf("Window::~Window()\n");
    al_destroy_display(display_);
}