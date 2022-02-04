#include "alcpp_font.hpp"

static const bool DEBUG = true;

Font::Font() 
    : font_(nullptr)
{
    if (DEBUG) printf("Font::Font()\n");
    font_ = al_create_builtin_font();
    if (!font_) throw "Error: failed to create font."; 
}

Font::~Font() {
    if (DEBUG) printf("Font::~Font()\n");
    al_destroy_font(font_);
}