#pragma once

struct Direction {
    Direction(bool n, bool s, bool e, bool w)
        : north(n), south(s), east(e), west(w) {};
    bool north;
    bool south;
    bool east;
    bool west;
};