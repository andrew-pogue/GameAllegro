#include "ui_text.hpp"

static const bool DEBUG = true;

Text::Text(std::string s, int x, int y)
    : Prop(x, y, 0), string(s), font()
{
    if (DEBUG) printf("Text::Text(%s, %i, %i)\n", s.c_str(), x, y);
    this->color = al_map_rgb(255, 255, 255);
};

Text::~Text() {
    if (DEBUG) printf("Text::~Text()\n");
}

void Text::render() const {
    // if (DEBUG) printf("Text::render()\n");
    al_draw_text(this->font, this->color,
        this->x_, this->y_, 0, this->string.c_str());
}

void Text::set_color(int r, int g, int b) {
    this->color = al_map_rgb(r, g, b);
}

void Text::set_color(int r, int g, int b, int a) {
    this->color = al_map_rgba(r, g, b, a);
}