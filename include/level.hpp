#pragma once
#include "alcpp_display.hpp"
#include "alcpp_font.hpp"

struct Level {
    Level() : x_(30), y_(30), z_(3), tile_size_(25) {
        printf("Level::Level()\n");
        color_ = al_map_rgb(255, 255, 255);
    }
    
    ~Level() { printf("Level::~Level()\n"); }

    void render(const Display& display) const {
        for (int x = tile_size_; x < display.get_width(); x += tile_size_) {
            for (int y = tile_size_; y < display.get_height(); y += tile_size_) {
                al_draw_text(font_, color_, x, y, 0, "#");
            }
        }
    }
private:
    int x_, y_, z_; // the dimensions
    int tile_size_;
    Font font_;
    ALLEGRO_COLOR color_;
};