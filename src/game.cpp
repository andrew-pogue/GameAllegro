#include "game.hpp"

static const bool DEBUG = true;

Game::Game()
    : display(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0), frame_timer(1.0 / 30.0), event_queue(),
        input_handler(), player(0, 0, 0), actors(), independent_props()
{
    if (DEBUG) printf("Game::Game()\n");
    this->event_queue.register_event_source(al_get_keyboard_event_source());
    this->event_queue.register_event_source(this->display);
    this->event_queue.register_event_source(this->frame_timer);
    this->load();
}

Game::~Game() {
    if (DEBUG) { printf("Game::~Game()\n"); }

    for (auto it = this->actors.begin(); it != this->actors.end(); it++) {
        delete (*it);
    }

    for (auto it = this->independent_props.begin(); it != this->independent_props.end(); it++) {
        delete (*it);
    }
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
            handle_input();
            redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            this->input_handler.key_pressed(event.keyboard.keycode);
            break;
        case ALLEGRO_EVENT_KEY_UP:
            this->input_handler.key_released(event.keyboard.keycode);
            break;
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

    #undef KEY_SEEN
    #undef KEY_RELEASED
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

void Game::handle_input() {
    // if (DEBUG) printf("Game::handle_input(ALLEGRO_EVENT)\n");
    if (this->input_handler[ALLEGRO_KEY_UP])
        this->player.move(Direction(1,0,0,0));
    if (this->input_handler[ALLEGRO_KEY_DOWN])
        this->player.move(Direction(0,1,0,0));
    if (this->input_handler[ALLEGRO_KEY_RIGHT])
        this->player.move(Direction(0,0,1,0));
    if (this->input_handler[ALLEGRO_KEY_LEFT])
        this->player.move(Direction(0,0,0,1));
    this->input_handler.key_seen_all();
}