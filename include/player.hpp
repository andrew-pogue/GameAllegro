#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "actor.hpp"

class Player : Actor {
public:
    Player(int x, int y, int z) : Actor(x, y, z) {
        this->font = al_create_builtin_font();
        if (!this->font) throw "Error: failed to create font."; 
        this->color = al_map_rgb(255, 255, 255);
        this->c = '@';
    };

    void act() const override {
    }

    void render() const override {
        al_draw_text(this->font, this->color, this->x_ + WINDOW_WIDTH / 2,
            this->y_ + WINDOW_HEIGHT / 2, 0, &this->c);
    }

    void move(Direction direction) {
        this->x_ += direction.east - direction.west;
        this->y_ += direction.north - direction.south;
    }

private:
    char c;
    ALLEGRO_FONT* font;
    ALLEGRO_COLOR color;
};