#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include "actor.hpp"
#include "alcpp_font.hpp"

class Player : Actor {
public:
    Player(int, int, int);
    ~Player();
    void act() const override;
    void render() const override;
    void move(Direction);
private:
    char c;
    Font font;
    ALLEGRO_COLOR color;
};