#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <list>

#include "actor.hpp"
#include "prop.hpp"

#include "text.hpp"
#include "player.hpp"

class Game {
private:
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_TIMER* frame_timer;
    std::list<Actor*> actors;
    std::list<Prop*> independent_props;
    Player player;

    void load();
    bool init_allegro();
    void update();
    void render();
    void handle_input(ALLEGRO_EVENT);
    void handle_timers();
    void handle_commands();
public:
    Game();
    ~Game();
    void play();
};

// transform class?