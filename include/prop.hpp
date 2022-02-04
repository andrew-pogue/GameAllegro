#pragma once
#include "entity.hpp"

// can't perform commands
struct Prop : Entity {
    Prop(int x, int y, int z) : Entity(x, y, z) {};
    virtual ~Prop() {}
};