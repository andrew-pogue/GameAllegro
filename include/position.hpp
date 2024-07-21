#pragma once

struct Position {
    int x,y,z;

    void operator= (const Position& other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    bool operator< (const Position& other) const {
        return z < other.z 
            || x < other.x
            || y < other.y;
    }

    bool operator<= (const Position& other) const {
        return z <= other.z 
            || x <= other.x
            || y <= other.y;
    }

    bool operator> (const Position& other) const {
        return z > other.z 
            || x > other.x
            || y > other.y;
    }

    bool operator>= (const Position& other) const {
        return z >= other.z 
            || x >= other.x
            || y >= other.y;
    }

    bool operator== (const Position& other) const {
        return z == other.z
            && y == other.y
            && x == other.x;
    }

    bool operator!= (const Position& other) const {
        return z != other.z
            || y != other.y
            || x != other.x;
    }
};

struct Direction {
    Direction() : north(0), south(0), 
        east(0), west(0), up(0), down(0)
    {}

    bool north  : 1, 
        south   : 1,
        east    : 1,
        west    : 1,
        up      : 1,
        down    : 1;

    void operator= (const Direction& other) {
        north = other.north;
        south = other.south;
        east = other.east;
        west = other.west;
        up = other.up;
        down = other.down;
    }

    void operator+ (const Direction& other) {
        north += other.north;
        south += other.south;
        east += other.east;
        west += other.west;
        up += other.up;
        down += other.down;
    }

    void operator- (const Direction& other) {
        north -= other.north;
        south -= other.south;
        east -= other.east;
        west -= other.west;
        up -= other.up;
        down -= other.down;
    }

    bool operator== (const Direction& other) {
        return north == other.north
            && south == other.south
            && east == other.east
            && west == other.west
            && up == other.up
            && down == other.down;
    }
};