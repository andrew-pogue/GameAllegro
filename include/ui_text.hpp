#pragma once
#include <stdio.h>
#include <string>
#include <allegro5/allegro.h>
#include "alcpp_font.hpp"
#include "prop.hpp"

struct Text : Prop {
    Text(std::string, int, int);
    Text(std::string, int, int, int, int, int);
    ~Text();

    void render(int, int) const override;
    void set_color(int, int, int);
    void set_color(int, int, int, int);

private:
    std::string string_;
    Font font_;
    ALLEGRO_COLOR color_;
};