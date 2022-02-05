#pragma once
#include <stdio.h>
#include <string>
#include <allegro5/allegro.h>
#include "alcpp_font.hpp"
#include "prop.hpp"

struct Text : Prop {
    Text(std::string, int x, int y);
    Text(std::string, int x, int y, int r, int g, int b);
    ~Text();

    void render(int x, int y) const override;
    void set_color(int r, int g, int b);
    void set_color(int r, int g, int b, int a);

private:
    std::string string_;
    Font font_;
    ALLEGRO_COLOR color_;
};