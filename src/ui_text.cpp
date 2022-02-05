#include "ui_text.hpp"

static const bool DEBUG = true;

Text::Text(std::string s, int x, int y)
    : Prop(x, y, 0), string_(s), font_()
{
    if (DEBUG) printf("Text::Text(%s, %i, %i)\n", s.c_str(), x, y);
    color_ = al_map_rgb(255, 255, 255);
};

Text::Text(std::string s, int x, int y, int r, int g, int b)
    : Prop(x, y, 0), string_(s), font_()
{
    if (DEBUG) printf("Text::Text(%s, %i, %i, %i, %i, %i)\n", s.c_str(), x, y, r, g, b);
    color_ = al_map_rgb(r, g, b);
};

Text::~Text() {
    if (DEBUG) printf("Text::~Text()\n");
}

void Text::render(int x, int y) const {
    // if (DEBUG) printf("Text::render()\n");
    al_draw_text(font_, color_, x, y, 0, string_.c_str());
}

void Text::set_color(int r, int g, int b) {
    color_ = al_map_rgb(r, g, b);
}

void Text::set_color(int r, int g, int b, int a) {
    color_ = al_map_rgba(r, g, b, a);
}