#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <forward_list>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "entity.hpp"
#include "tile.hpp"
#include "keylog.hpp"
#include "display.hpp"
#include "event_queue.hpp"
#include "timer.hpp"
#include "font.hpp"

#include "text.hpp"
#include "glyh.hpp"

// #include "ui_text.hpp"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int PLAYER_SPEED = 10;

class Game {
public:
    Game(std::string font, int font_size);
    ~Game();
    void play();
private:
    Display display_;
    Timer frame_timer_;
    EventQueue event_queue_;
    KeyLog keylog_;
    FontManager font_manager_;
    std::string font_path_;
    unsigned short font_size_;
    Entity* player_;
    std::forward_list<Tile> tile_list_;

    void load();
    void render();
    void update();

    // Position adjust_for_rendering(const Position& Position) const;
    void render(const Tile& tile) const;
    
    void handle_input();
    // void handle_timers();
    // void handle_commands();

    void load_test_unicode_font();
    void load_test_player_fov();
};