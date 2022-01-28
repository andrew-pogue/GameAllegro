#include "game.hpp"

Game::Game() {
    if (DEBUG) {
        std::cout << "Game::Game() called\n";
    }

    if (!al_init()) {
        throw "Error: Couldn't initialize Allegro.";
    }

    if (!al_init_font_addon()) { 
        throw "Error: Couldn't initialize Allegro font addon.";
    }

    if (!al_install_keyboard()) { 
        throw "Error: Couldn't initialize Allegro keyboard addon."; 
    }

    this->font = al_create_builtin_font();
    if (!this->font) {
        throw "Error: Couldn't create font."; 
    }

    this->display = al_create_display(640, 480);
    if (!this->display) {
        throw "Error: Couldn't create display.";
    }

    this->event_queue = al_create_event_queue();
    if (!this->event_queue) {
        throw "Error: Couldn't create event queue."; 
    }

    this->frame_timer = al_create_timer(1.0 / 30.0);
    if (!this->frame_timer) {
        throw "Error: Couldn't create timer."; 
    }

    al_register_event_source(this->event_queue, al_get_keyboard_event_source());
    al_register_event_source(this->event_queue, al_get_display_event_source(this->display));
    al_register_event_source(this->event_queue, al_get_timer_event_source(this->frame_timer));
}

void Game::play() {
    if (DEBUG) {
        std::cout << "Game::play() called\n";
    }

    bool play = true, redraw = true;
    ALLEGRO_EVENT event;
    al_start_timer(this->frame_timer);
    while (play) {
        al_wait_for_event(this->event_queue, &event);
        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            play = false;
            break;
        }

        if (redraw && al_is_event_queue_empty(this->event_queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(this->font, al_map_rgb(255, 255, 255), 320, 240, 0, "Hello world!");
            al_flip_display();
            redraw = false;
        }
    }
}

Game::~Game() {
    if (DEBUG) {
        std::cout << "Game::~Game() called\n";
    }

    al_destroy_font(this->font);
    al_destroy_timer(this->frame_timer);
    al_destroy_event_queue(this->event_queue);
    al_destroy_display(this->display);
}