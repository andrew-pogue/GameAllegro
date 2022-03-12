#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "entity.hpp"

struct Glyph : Entity {
    Glyph(int codepoint, ALLEGRO_COLOR color)
        : codepoint_(codepoint), color_(color)
    {}
    
    ~Glyph() {}

    void render(float x, float y) const override {
        al_draw_glyph(
            font_,
            color_,
            x + x_ * Tile::size,
            y + y_ * Tile::size,
            codepoint_
        );
    }

    void set_color(const ALLEGRO_COLOR& color) { 
        color_.r = color.r;
        color_.b = color.b;
        color_.g = color.g;
        color_.a = color.a;
    }

    void set_font(const ALLEGRO_FONT* font) {
        font_ = font;
    }
private:
    int codepoint_;
    ALLEGRO_COLOR color_;
    const ALLEGRO_FONT* font_;
};