#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "actor.hpp"

class Player : Actor {
public:
    Player(int, int, int);
    ~Player();
    void act() const override;
    void render() const override;
    void move(Direction);
private:
    char c;
    ALLEGRO_FONT* font;
    ALLEGRO_COLOR color;
};