#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <string>

#include "prop.hpp"

struct Text : Prop {
    void render() const override;

    std::string string;
    ALLEGRO_FONT* font;
    ALLEGRO_COLOR color;

    Text(std::string, int, int);
    ~Text();
};