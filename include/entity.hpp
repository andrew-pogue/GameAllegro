#pragma once

struct Entity {
    Entity(int x, int y, int z) : x_(x), y_(y), z_(z) {};
    virtual ~Entity() {};
    virtual void render(int x, int y) const = 0;
    int get_x() const { return x_; }
    int get_y() const { return y_; }
    int get_z() const { return z_; }
protected:
    int x_, y_, z_;
};