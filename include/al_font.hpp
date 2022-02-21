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