#include "game.hpp"

static const bool DEBUG = true;

bool Game::init() {
    if (DEBUG) printf("Game::init()\n");
    if (Game::is_init) return true;

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

    Game::is_init = true;
    return true;
}

Game::Game()
    : display(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0), frame_timer(1.0 / 30.0), event_queue(),
        player(0, 0, 0), actors(), independent_props()
{
    if (DEBUG) printf("Game::Game()\n");
    this->event_queue.register_event_source(al_get_keyboard_event_source());
    this->event_queue.register_event_source(this->display);
    this->event_queue.register_event_source(this->frame_timer);
    this->load();
}

void Game::play() {
    if (DEBUG) printf("Game::play()\n");

    bool play = true, redraw = true;
    ALLEGRO_EVENT event;
    al_start_timer(this->frame_timer);
    while (play) {
        al_wait_for_event(this->event_queue, &event);
        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            break;
        // case ALLEGRO_EVENT_KEY_DOWN:
        //     handle_input(event);
        //     break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            play = false;
            break;
        }

        // this->update();

        if (redraw && al_is_event_queue_empty(this->event_queue)) {
            this->render();
            redraw = false;
        }
    }
}

Game::~Game() {
    if (DEBUG) { printf("Game::~Game()\n"); }

    for (auto it = this->actors.begin(); it != this->actors.end(); it++) {
        delete (*it);
    }
}

void Game::update() {
    if (DEBUG) printf("Game::update()\n");
    for (auto it = this->actors.begin(); it != this->actors.end(); it++) {
        (*it)->act();
    }
}

void Game::render() {
    // if (DEBUG) printf("Game::render()\n");

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
    if (DEBUG) printf("Game::load()\n");
    this->independent_props.push_back(new Text("Hello World!", 10, 10));
    this->independent_props.push_back(new Text("Allegro is cool!", 70, 70));
}

void Game::handle_input(ALLEGRO_EVENT event) {
    if (DEBUG) printf("Game::handle_input(ALLEGRO_EVENT)\n");
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