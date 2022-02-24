#pragma once
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <queue>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "al_display.hpp"
#include "al_event_queue.hpp"
#include "al_timer.hpp"
#include "al_font.hpp"

#include "io_keylog.hpp"

#include "flecs.h"
#include "components.hpp"

// #include "ui_text.hpp"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int GAME_SPEED = 4;
const int FRAMES_PER_SECOND = 30;

class Game {
public:

    Game(std::string font, int font_size);
    ~Game();
    void play();
    void load();

private:

    flecs::world world_;
    Display display_;
    Timer frame_timer_;
    EventQueue event_queue_;
    KeyLog keylog_;
    FontManager font_manager_;
    std::string font_path_;
    int font_size_, tile_size_;
    flecs::entity player_;
    std::vector<unsigned short> action_wait_;
    unsigned int move_wait_;
    bool traveling_;
    std::queue<CMove> moveQ_;

    void process_input();
    void render();

    int translate_x(const int& x) const;
    int translate_y(const int& y) const;
    bool display_contains(const int& x, const int& y) const;

    void load_game_systems();
    void load_move_systems();
    void load_glyph_systems();
    void load_text_systems();
    void load_test_player_fov();
    void foo();
};