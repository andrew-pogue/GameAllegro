#include "character.hpp"

static const bool DEBUG = true;

Character::Character(int x, int y, int z)
    : Actor(x, y, z),  str_("@"), font_(), direction_(1, 0, 0, 0)
{
    if (DEBUG) printf("Character::Character(%i, %i, %i)\n", x, y, z);
    color_ = al_map_rgb(255, 255, 255);
};

Character::~Character() {
    if (DEBUG) printf("Character::~Character()\n");
}

void Character::act() const {
    if (DEBUG) printf("Character::act()\n");
}

void Character::render() const {
    // if (DEBUG) printf("Character::render()\n");
    al_draw_text(font_, color_, x_, y_, 0, str_.c_str());
}

void Character::move(Direction direction) {
    // if (DEBUG) printf("Character::move(Direction)\n");
    x_ += direction.east - direction.west;
    y_ += direction.south - direction.north;
}