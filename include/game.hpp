#pragma once
#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include <forward_list>
#include <queue>

#include "entity.hpp"

#include "io_keylog.hpp"

#include "al_display.hpp"
#include "al_event_queue.hpp"
#include "al_timer.hpp"

#include "entity_text.hpp"
#include "entity_glyh.hpp"

#include "math.h"

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
    
    Entity* player_;
    // This list takes responsibility for de-allocating objects.
    std::forward_list<Entity*> entities_;
    // std::forward_list<ui::Element*> ui_elements_;

    const std::string font_;
    const int font_size_;

    void load();
    void render();
    
    void handle_input();
    // void handle_timers();
    // void handle_commands();

    void load_test_unicode_font();
    void load_test_player_fov();
};