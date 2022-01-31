#pragma once
#include "entity.hpp"

// gets acted on by actors
struct Prop : Entity {
    Prop(int x, int y, int z) : Entity(x, y, z) {};
    virtual ~Prop() {}
};