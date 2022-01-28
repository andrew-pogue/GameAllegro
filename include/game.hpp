#pragma once
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

const bool DEBUG = true;

class Game {
private:
    ALLEGRO_FONT* font;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_TIMER* frame_timer;

public:
    Game();
    ~Game();
    void play();
}; // class Game
