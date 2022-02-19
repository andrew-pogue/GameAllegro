#include "al_font.hpp"

static const bool DEBUG = true;

FontManager::FontManager() 
    : font_map_()
{
    if (DEBUG) printf("FontManager::FontManager()\n");
    load_builtin();
}

FontManager::~FontManager() {
    if (DEBUG) printf("FontManager::~FontManager()\n");
    for (auto font : font_map_) {
        al_destroy_font(font.second);
    }
}

ALLEGRO_FONT* FontManager::operator[](const std::string path) {
    return font_map_.at(path);
}

bool FontManager::load_bmp(std::string path) {
    if (DEBUG) printf("FontManager::load_bmp(%s)\n", path.c_str());
    if (path.size() == 0) return true;
    if (font_map_.find(path) != font_map_.end()) return true;
    ALLEGRO_FONT* font = al_load_bitmap_font(path.c_str());
    if (font) {
        font_map_[path] = font;
        return true;
    }
    return false;
}

bool FontManager::load_ttf(std::string path, int size) {
    if (DEBUG) printf("FontManager::load_ttf(%s, %i)\n", path.c_str(), size);
    if (path.size() == 0) return true;
    if (font_map_.find(path) != font_map_.end()) return true;
    ALLEGRO_FONT* font = al_load_ttf_font(path.c_str(), size, ALLEGRO_ALIGN_CENTER);
    if (font) {
        font_map_[path] = font;
        return true;
    }
    return false;
}

bool FontManager::load_font(std::string path, int size) {
    if (DEBUG) printf("FontManager::load_font(%s, %i)\n", path.c_str(), size);
    if (path.size() == 0) return true;
    if (font_map_.find(path) != font_map_.end()) return true;
    ALLEGRO_FONT* font = al_load_font(path.c_str(), size, ALLEGRO_ALIGN_CENTER);
    if (font) {
        font_map_[path] = font;
        return true;
    }
    return false;
}

bool FontManager::load_builtin() {
    if (DEBUG) printf("FontManager::load_builtin()\n");
    ALLEGRO_FONT* font = al_create_builtin_font();
    if (font) {
        font_map_[""] = font;
        return true;
    }
    return false;
}