#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <list>

#include "actor.hpp"
#include "prop.hpp"

#include "display.hpp"
#include "event_queue.hpp"
#include "timer.hpp"

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

    static inline bool is_init = false;

    void update();
    void render();
    
    void handle_input(ALLEGRO_EVENT);
    void handle_timers();
    void handle_commands();
public:
    /**
     * Initializes Allegro core and subsystems and installs input devices.
     * Should only happen once, even with multiple Game objects.
     **/
    static bool init();

    Game();
    ~Game();
    void play();
};

// transform class?