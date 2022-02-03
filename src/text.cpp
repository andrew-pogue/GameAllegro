#include "text.hpp"

static const bool DEBUG = true;

Text::Text(std::string s, int x, int y)
    : Prop(x, y, 0), string(s), font(nullptr)
{
    if (DEBUG) printf("Text::Text(%s, %i, %i)\n", s.c_str(), x, y);
    this->font = al_create_builtin_font();
    if (!this->font) throw "Error: failed to create font."; 
    this->color = al_map_rgb(255, 255, 255);
};

Text::~Text() {
    if (DEBUG) printf("Text::~Text()\n");
    al_destroy_font(this->font);
}

void Text::render() const {
    // if (DEBUG) printf("Text::render()\n");
    al_draw_text(this->font, this->color,
        this->x_, this->y_, 0, this->string.c_str());
}