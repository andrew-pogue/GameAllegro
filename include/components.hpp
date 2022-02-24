#pragma once
#include <string>
#include <stdint.h>
#include <allegro5/allegro.h>

struct CPosition {
    // Coordinates in tiles.
    float x = 0.0, y = 0.0;
    int z = 0;
};

struct CMove {
    // Destination in tiles relative to current position.
    float x = 0.0, y = 0.0;
    int z = 0;
    unsigned short cooldown = 0;
    bool in_progress = false;
};

struct CGlyph {
    int codepoint;
    ALLEGRO_COLOR color = al_map_rgb(200,200,200);
};

struct CText {
    std::string string;
    ALLEGRO_COLOR color = al_map_rgb(200,200,200);
    int render_flag = 0;
};

struct CDirection {
    bool north = false, south = false,
        east = false, west = false;
};

struct CRender {
    bool is_enabled = false;
    /**
     * Represents the coordinates in pixels relative to the display origin.
     * The display origin is at the top left corner of the window.
     * The y-axis for the display increases as you go down,
     * the x-axis increases as you go right.
     **/
    float x = 0.0, y = 0.0;
    int z = 0;
};

// investigate flecs switch and flecs case