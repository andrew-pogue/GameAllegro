#pragma once
#include <stdio.h>
#include <string>
#include <allegro5/allegro.h>
#include "alcpp_font.hpp"
#include "prop.hpp"

struct Text : Prop {
    Text(std::string, int, int);
    ~Text();

    void render() const override;
    void set_color(int r, int g, int b);
    void set_color(int r, int g, int b, int a);

private:
    std::string string;
    Font font;
    ALLEGRO_COLOR color;
};