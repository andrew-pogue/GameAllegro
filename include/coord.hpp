#pragma once

struct Coord {
    int x,y,z;

    void operator= (const Coord& other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    bool operator< (const Coord& other) const {
        return z < other.z 
            || x < other.x
            || y < other.y;
    }

    bool operator<= (const Coord& other) const {
        return z <= other.z 
            || x <= other.x
            || y <= other.y;
    }

    bool operator> (const Coord& other) const {
        return z > other.z 
            || x > other.x
            || y > other.y;
    }

    bool operator>= (const Coord& other) const {
        return z >= other.z 
            || x >= other.x
            || y >= other.y;
    }

    bool operator== (const Coord& other) const {
        return z == other.z
            && y == other.y
            && x == other.x;
    }

    bool operator!= (const Coord& other) const {
        return z != other.z
            || y != other.y
            || x != other.x;
    }
};

struct Direction {
    bool north = false, 
        south = false,
        east = false,
        west = false,
        up = false,
        down = false;

    void operator= (const Direction& other) {
        north = other.north;
        south = other.south;
        east = other.east;
        west = other.west;
        up = other.up;
        down = other.down;
    }
};