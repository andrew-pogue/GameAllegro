#pragma once
#include <string>
#include <allegro5/allegro.h>
#include "entity.hpp"
#include "al_font.hpp"

namespace entity {

    struct Text : Entity {
        Text(std::string string, Coord coord, Font font)
            : Entity(coord), string_(string), font_(font)
        {}
        
        Text(std::string string, Coord coord, ALLEGRO_FONT* font, ALLEGRO_COLOR color)
            : Entity(coord), string_(string), font_(font, color)
        {}

        ~Text() {}

        void render(int x, int y) const override { 
            al_draw_text(
                font_.al_font, 
                font_.color,
                x, y,
                font_.render_flag,
                string_.c_str()
            ); 
        }

        operator std::string() const
        { return string_; }

        void set_color(ALLEGRO_COLOR color)
        { font_.color = color; }

        void set_font(ALLEGRO_FONT* font)
        { font_.al_font = font; }

    private:
        std::string string_;
        Font font_;
    };
}