#pragma once
#include "entity.hpp"
#include "command.hpp"
#include "direction.hpp"

// can perform commands
struct Actor : Entity {
    Actor(int x, int y, int z) : Entity(x, y, z) {};
    virtual ~Actor() {};
    virtual void act() const = 0;

    // Support for commands:
    virtual void move(Direction) {};
};