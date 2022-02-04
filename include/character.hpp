#pragma once
#include <stdio.h>
#include <string>
#include <allegro5/allegro.h>
#include "actor.hpp"
#include "alcpp_font.hpp"
#include "direction.hpp"

class Character : Actor {
public:
    Character(int, int, int);
    ~Character();
    void act() const override;
    void render() const override;
    void move(Direction);
private:
    std::string str_;
    Font font_;
    ALLEGRO_COLOR color_;
    Direction direction_; // The direction the character is facing.
};