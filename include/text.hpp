#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <string>

#include "entity.hpp"

struct Text : Entity {
    void render() const;
    void update();

    std::string string;
    ALLEGRO_FONT* font;
    ALLEGRO_COLOR color;
    int x, y;

    Text();
    Text(std::string s);
    Text(std::string s, int x, int y);
    Text(std::string s, ALLEGRO_COLOR c);
    Text(std::string s, ALLEGRO_FONT* f);
    Text(std::string s, ALLEGRO_FONT* f, ALLEGRO_COLOR c);
    ~Text();
};