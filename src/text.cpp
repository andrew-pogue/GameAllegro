#include "text.hpp"
   
Text::Text() 
    : string()
{
    printf("! Text(std::string) !\n");
    this->font = al_create_builtin_font();
    if (!this->font) throw "Error: Couldn't create Allegro builtin font."; 
    this->color = al_map_rgb(255, 255, 255);
}

Text::Text(std::string s)
    : string(s)
{
    printf("! Text(std::string) !\n");
    this->font = al_create_builtin_font();
    if (!this->font) throw "Error: Couldn't create Allegro builtin font."; 
    this->color = al_map_rgb(255, 255, 255);
}

Text::Text(std::string s, ALLEGRO_COLOR c)
    : string(s), color(c)
{
    printf("! Text(std::string, ALLEGRO_COLOR) !\n");
    this->font = al_create_builtin_font();
    if (!this->font) throw "Error: Couldn't create Allegro builtin font.";
}

Text::Text(std::string s, ALLEGRO_FONT* f)
    : string(s), font(f)
{
    printf("! Text(std::string, ALLEGRO_FONT*) !\n");
    if (!this->font) throw "Error: Invalid font.";
    this->color = al_map_rgb(255, 255, 255);
}

Text::Text(std::string s, int x, int y)
    : string(s), x(x), y(y)
{
    printf("! Text(std::string, int, int) !\n");
    this->font = al_create_builtin_font();
    if (!this->font) throw "Error: Couldn't create Allegro builtin font."; 
    this->color = al_map_rgb(255, 255, 255);
}

Text::Text(std::string s, ALLEGRO_FONT* f, ALLEGRO_COLOR c) 
    : string(s), font(f), color(c)
{
    printf("! Text(std::string, ALLEGRO_FONT*, ALLEGRO_COLOR) !\n");
    if (!this->font) throw "Error: Invalid font.";
}

Text::~Text() {
    printf("! ~Text() !\n");
    al_destroy_font(this->font);
}

void Text::render() const {
    al_draw_text(this->font, al_map_rgb(255, 255, 255),
        this->x, this->y, 0, this->string.c_str());
}

void Text::update() {
    
}