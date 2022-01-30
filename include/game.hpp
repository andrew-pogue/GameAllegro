#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <list>

#include "entity.hpp"
#include "text.hpp"

const bool DEBUG = true;

class Game {
private:
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_TIMER* frame_timer;
    std::list<Entity*> entities;

    void load_entities();
    bool init_allegro();
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