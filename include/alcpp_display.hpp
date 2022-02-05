#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include "alcpp_init.hpp"
#include "entity.hpp"

// Wrapper for ALLEGRO_DISPLAY with some added functionality
struct Display : Init {
    // Assumes that the Allegro core library was already initialized.
    Display(int, int);
    ~Display();

    operator ALLEGRO_DISPLAY*(void)
    { return display_; }

    int get_height() const
    { return height_; }

    int get_width() const
    { return width_; }

    void follow(Entity* entity) {
        // problem: display shouldn't be able to modify entity's x, y, z values
        // but entity's x, y, z values are not of a constant type
        // use events?
        follow_x_ = &(entity->x_);
        follow_y_ = &(entity->y_);
        follow_z_ = &(entity->z_);
    }

    // for some reason i have to shift it towards the top left corner
    // by about 8 pixels to center it in the middle of the screen
    // otherwise the followed entity won't be centered on the screen vvv

    int get_x() const { return *follow_x_ - (width_ / 2) + 8; }
    int get_y() const { return *follow_y_ - (height_ / 2) + 8; }
    int get_z() const { return *follow_z_; }

private:
    int *follow_x_, *follow_y_, *follow_z_; // position of followed entity in game world
    ALLEGRO_DISPLAY* display_;
    int width_;
    int height_;
};