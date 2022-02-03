#pragma once

struct Entity {
    Entity(int x, int y, int z) : x_(x), y_(y), z_(z) {};
    virtual ~Entity() {};
    virtual void render() const = 0;
protected:
    int x_, y_, z_;
};