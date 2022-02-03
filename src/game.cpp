#include "game.hpp"

static const bool DEBUG = false;

bool Game::init_allegro() {
    if (DEBUG) { printf("Game::init_allegro() called\n"); }

    if (!al_init()) {
        printf("Error: failed to initialize Allegro.\n");
        return false;
    }

    if (!al_init_font_addon()) { 
        printf("Error: failed to initialize Allegro font addon.\n");
        return false;
    }

    if (!al_install_keyboard()) { 
        printf("Error: failed to install keyboard.\n");
        return false;
    }

    if (!al_install_mouse()) { 
        printf("Error: failed to install mouse.\n");
        return false;
    }

    this->event_queue = al_create_event_queue();
    if (!this->event_queue) {
        throw "Error: failed to create event queue."; 
    }

    this->frame_timer = al_create_timer(1.0 / 30.0);
    if (!this->frame_timer) {
        throw "Error: failed to create timer."; 
    }

    al_register_event_source(this->event_queue, al_get_keyboard_event_source());
    al_register_event_source(this->event_queue, al_get_display_event_source(this->display));
    al_register_event_source(this->event_queue, al_get_timer_event_source(this->frame_timer));

    return true;
}

Game::Game() : player(0, 0, 0) {
    if (DEBUG) { printf("Game::Game() called\n"); }
    if (!this->init_allegro())
        throw "Error: failed to construct Game!";
    this->load();
}

void Game::play() {
    if (DEBUG) { printf("Game::play() called\n"); }

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
            handle_input(event);
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            play = false;
            break;
        }

        this->update();

        if (redraw && al_is_event_queue_empty(this->event_queue)) {
            this->render();
            redraw = false;
        }
    }
}

Game::~Game() {
    if (DEBUG) { printf("Game::~Game() called\n"); }

    for (auto it = this->actors.begin(); it != this->actors.end(); it++) {
        delete (*it);
    }

    al_destroy_timer(this->frame_timer);
    al_destroy_event_queue(this->event_queue);
}

void Game::update() {
    for (auto it = this->actors.begin(); it != this->actors.end(); it++) {
        (*it)->act();
    }
}

void Game::render() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    for (auto it = this->independent_props.begin(); it != this->independent_props.end(); it++) {
        (*it)->render();
    }

    for (auto it = this->actors.begin(); it != this->actors.end(); it++) {
        (*it)->render();
    }

    player.render();
    
    al_flip_display();
}

void Game::load() {
    this->independent_props.push_back(new Text("Hello World!", 10, 10));
    this->independent_props.push_back(new Text("Allegro is cool!", 70, 70));
}

void Game::handle_input(ALLEGRO_EVENT event) {
    ALLEGRO_KEYBOARD_STATE* keyboard = NULL;
    al_get_keyboard_state(keyboard);
    if (al_key_down(keyboard, ALLEGRO_KEY_UP)) {
        this->player.move(Direction(1,0,0,0));
    } if (al_key_down(keyboard, ALLEGRO_KEY_DOWN)) {
        this->player.move(Direction(0,1,0,0));
    } if (al_key_down(keyboard, ALLEGRO_KEY_LEFT)) {
        this->player.move(Direction(0,0,0,1));
    } if (al_key_down(keyboard, ALLEGRO_KEY_RIGHT)) {
        this->player.move(Direction(0,0,1,0));
    }
}