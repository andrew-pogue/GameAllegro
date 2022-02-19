#pragma once
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// Wrapper for ALLEGRO_FONT
struct FontManager {
    FontManager();
    ~FontManager();

    ALLEGRO_FONT* operator[](const std::string);

    bool load_font(std::string path, int size);
    bool load_ttf(std::string path, int size);
    bool load_bmp(std::string path);

private:
    std::unordered_map<std::string, ALLEGRO_FONT*> font_map_;

    bool load_builtin();
};

struct Font {
    Font(const Font& other)
        : al_font(other.al_font), color(other.color), render_flag(other.render_flag)
    {}

    Font(ALLEGRO_FONT* font, ALLEGRO_COLOR color)
        : al_font(font), color(color), render_flag()
    {}

    Font(ALLEGRO_FONT* font, ALLEGRO_COLOR color, int flag)
        : al_font(font), color(color), render_flag(flag)
    {}
    
    ~Font() {}

    void operator=(const Font& other) {
        al_font = other.al_font;
        color = other.color;
        render_flag = other.render_flag;
    }

    ALLEGRO_FONT* al_font;
    ALLEGRO_COLOR color;
    int render_flag;

};