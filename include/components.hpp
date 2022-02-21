#pragma once
#include <string>
#include <allegro5/allegro.h>

struct CPosition {
    int x,y,z;
};

struct CMove {
    int x, y, z;
};

struct CGlyph {
    int codepoint;
    ALLEGRO_COLOR color;
};

struct CText {
    std::string string;
    ALLEGRO_COLOR color;
    int render_flag;
};

struct CDirection {
    bool north, south,
        east, west;
};

struct CRender {
    bool is_enabled;
    int x,y,z;
};

// Use flecs switch and flecs case instead?
struct CViewpoint {};