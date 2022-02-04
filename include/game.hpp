#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <list>

#include "actor.hpp"
#include "prop.hpp"

#include "alcpp_display.hpp"
#include "alcpp_event_queue.hpp"
#include "alcpp_timer.hpp"

#include "text.hpp"
#include "player.hpp"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

class Game {
private:
    Display display;
    Timer frame_timer;
    EventQueue event_queue;
    
    Player player;
    std::list<Actor*> actors;
    std::list<Prop*> independent_props;

    void load();
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