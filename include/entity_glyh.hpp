#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "al_font.hpp"
#include "entity.hpp"

namespace entity {
    struct Glyph : Entity {
        Glyph(int codepoint, Coord coord, Font font)
            : Entity(coord), codepoint_(codepoint), font_(font)
        {}
        
        ~Glyph() {}

        void render(int x, int y) const override {
            al_draw_glyph(font_.al_font, font_.color, x, y, codepoint_);
        }
    private:
        int codepoint_;
        Font font_;
    };
} // namespace entity