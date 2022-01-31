#include "text.hpp"

Text::Text(std::string s, int x, int y) : string(s), Prop(x, y, 0) {
    this->font = al_create_builtin_font();
    if (!this->font) throw "Error: failed to create font."; 
    this->color = al_map_rgb(255, 255, 255);
};

Text::~Text() {
    al_destroy_font(this->font);
}

void Text::render() const {
    al_draw_text(this->font, this->color,
        this->x_, this->y_, 0, this->string.c_str());
}