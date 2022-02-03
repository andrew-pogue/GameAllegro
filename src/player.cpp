#include "player.hpp"

static const bool DEBUG = true;

Player::Player(int x, int y, int z)
    : Actor(x, y, z), font(nullptr)
{
    if (DEBUG) printf("Player::Player(%i, %i, %i)\n", x, y, z);
    this->font = al_create_builtin_font();
    if (!this->font) throw "Error: failed to create font."; 
    this->color = al_map_rgb(255, 255, 255);
    this->c = '@';
};

Player::~Player() {
    if (DEBUG) printf("Player::~Player()\n");
    al_destroy_font(this->font);
}

void Player::act() const {
    if (DEBUG) printf("Player::act()\n");
}

void Player::render() const {
    // if (DEBUG) printf("Player::render()\n");
    al_draw_text(this->font, this->color, this->x_,
        this->y_, 0, &this->c);
}

void Player::move(Direction direction) {
    if (DEBUG) printf("Player::move(Direction)\n");
    this->x_ += direction.east - direction.west;
    this->y_ += direction.north - direction.south;
}