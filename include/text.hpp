#pragma once
#include <string>
#include <allegro5/allegro.h>
#include "entity.hpp"

struct Text : Entity {
    Text(std::string string, ALLEGRO_FONT* font)
        : string_(string), font_(font)
    {}
    
    Text(std::string string, ALLEGRO_FONT* font, ALLEGRO_COLOR color)
        : string_(string), font_(font)
    {
        color_.r = color.r;
        color_.b = color.b;
        color_.g = color.g;
        color_.a = color.a;
    }

    Text(std::string string, ALLEGRO_FONT* font, ALLEGRO_COLOR color, int flag)
        : string_(string), font_(font), render_flag_(flag)
    {
        color_.r = color.r;
        color_.b = color.b;
        color_.g = color.g;
        color_.a = color.a;
    }

    ~Text() {}

    void render(float x, float y) const override { 
        al_draw_text(
            font_, 
            color_,
            x + x_ * Tile::size,
            y + y_ * Tile::size,
            render_flag_,
            string_.c_str()
        ); 
    }

    operator std::string() const { return string_; }

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
    std::string string_;
    ALLEGRO_COLOR color_;
    const ALLEGRO_FONT* font_;
    int render_flag_ = 0;
};