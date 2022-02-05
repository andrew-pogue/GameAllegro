#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <list>

#include "actor.hpp"
#include "prop.hpp"
#include "input.hpp"

#include "alcpp_display.hpp"
#include "alcpp_event_queue.hpp"
#include "alcpp_timer.hpp"

#include "ui_text.hpp"
#include "character.hpp"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

enum class KeyStatus {
    key_seen = 1,
    key_released = 2,
};

class Game {
private:
    Display display;
    Timer frame_timer;
    EventQueue event_queue;
    InputHandler input_handler;
    
    Character player;
    std::list<Actor*> actors;
    std::list<Prop*> independent_props;
    // render_queue

    void load();
    void update();
    void render();
    
    void handle_input();
    void handle_timers();
    void handle_commands();
public:
    Game();
    ~Game();
    void play();
};