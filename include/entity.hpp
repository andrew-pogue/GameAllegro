#pragma once

const bool DEBUG = true;
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

struct Entity {
    Entity(int x, int y, int z) : x_(x), y_(y), z_(z) {};
    virtual ~Entity() {};
    virtual void render() const = 0;
protected:
    int x_, y_, z_;
};