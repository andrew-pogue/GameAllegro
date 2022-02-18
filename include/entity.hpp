#pragma once

struct Coord {
    Coord(int X, int Y, int Z) : x(X), y(Y), z(Z) {}
    int x, y, z;
};

struct Entity {
    Entity(Coord coord) : x_(coord.x), y_(coord.y), z_(coord.z) {}
    virtual ~Entity() {}
    virtual void update() {}
    virtual void render(int x, int y) const {}

    size_t get_id() const { return id_; }
    int get_x() const { return x_; }
    int get_y() const { return y_; }
    int get_z() const { return z_; }

    // Support for commands:
    virtual void move(int x, int y, int z) {
        x_ += x;
        y_ += y;
        z_ += z;
    };
protected:
    size_t id_;
    int x_, y_, z_;
};