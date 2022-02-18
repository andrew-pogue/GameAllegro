#include "game.hpp"

static const bool DEBUG = true;

Game::Game()
    : display_(WINDOW_WIDTH, WINDOW_HEIGHT), frame_timer_(1.0 / 30.0),
        event_queue_(), keylog_(), font_manager_(), player_(nullptr), entities_()
{
    if (DEBUG) printf("Game::Game()\n");
    event_queue_.register_event_source(al_get_keyboard_event_source());
    event_queue_.register_event_source(al_get_mouse_event_source());
    event_queue_.register_event_source(display_);
    event_queue_.register_event_source(frame_timer_);
    load();
}

Game::~Game() {
    if (DEBUG) { printf("Game::~Game()\n"); }

    for (auto entity : entities_) {
        delete entity;
    }
}

void Game::play() {
    if (DEBUG) printf("Game::play()\n");

    bool play = true, redraw = true;
    ALLEGRO_EVENT event;

    frame_timer_.start();
    while (play) {
        event_queue_.wait_for_event(&event);

        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
            handle_input();
            redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            keylog_.set_key_pressed(event.keyboard.keycode);
            break;
        case ALLEGRO_EVENT_KEY_UP:
            keylog_.set_key_released(event.keyboard.keycode);
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            play = false;
            break;
        }

        for (auto entity : entities_) {
            entity->update();
        }

        if (redraw && event_queue_.is_empty()) {
            render();
            redraw = false;
        }
    }
}

void Game::load() {
    if (DEBUG) printf("Game::load()\n");

    if (!font_manager_.load_ttf(FONT_DEFAULT, FONT_SIZE)) {
        throw "Failed to load ttf font\"" + FONT_DEFAULT + "\"";
    }

    Font font(font_manager_[FONT_DEFAULT], al_map_rgb(255, 255, 255));

    entities_.push_front(new entity::Text("@", Coord(0, 0, 0), font));
    player_ = entities_.front();

    font.color = al_map_rgb(255, 0, 255);

    entities_.push_front(new entity::Text("Hello World!", Coord(10, 10, 0), font));

    font.color = al_map_rgb(155, 55, 155);

    entities_.push_front(new entity::Text("Allegro is cool!", Coord(70, 70, 0), font));

    font.color = al_map_rgb(0, 255, 0);
    
    entities_.push_front(new entity::Text("(0,0)", Coord(0,          0,      0), font));
    entities_.push_front(new entity::Text("(+,+)", Coord(320 - 8,    240 - 8,    0), font));
    entities_.push_front(new entity::Text("(-,-)", Coord(-320 + 8,   -240 + 8,   0), font));
    entities_.push_front(new entity::Text("(+,0)", Coord(320 - 8,    0,         0), font));
    entities_.push_front(new entity::Text("(-,0)", Coord(-320 + 8,   0,         0), font));
    entities_.push_front(new entity::Text("(0,+)", Coord(0,          240 - 8,    0), font));
    entities_.push_front(new entity::Text("(0,-)", Coord(0,        -240 + 8,   0), font));
    entities_.push_front(new entity::Text("(+,-)", Coord(320 - 8,    -240 + 8,   0), font));
    entities_.push_front(new entity::Text("(-,+)", Coord(-320 + 8,   240 - 8,    0), font));

    font.color = al_map_rgb(0, 0, 255);

    entities_.push_front(new entity::Text("Insert Fun Game Here", Coord(-50,       -20,        0), font));

    // ui_elements_.emplace_front(ui::Text("User Interface WIP", 10, 10, al_map_rgb(255, 0, 0)));
}

void Game::handle_input() {

    // if (DEBUG) printf("Game::handle_input(ALLEGRO_EVENT)\n");
    if (keylog_[ALLEGRO_KEY_UP]) {
        player_->move(0,PLAYER_SPEED,0);
    }

    if (keylog_[ALLEGRO_KEY_DOWN]) {
        player_->move(0,-PLAYER_SPEED,0);
    }

    if (keylog_[ALLEGRO_KEY_RIGHT]) {
        player_->move(PLAYER_SPEED,0,0);
    }

    if (keylog_[ALLEGRO_KEY_LEFT]) {
        player_->move(-PLAYER_SPEED,0,0);
    }

    keylog_.set_all_keys_seen();
}

/**
 * Renders all entities such that only entities that are visible on screen are rendered.
 **/
void Game::render() {
    al_clear_to_color(al_map_rgb(0, 0, 0));

    ALLEGRO_VERTEX v[] = {
        { .x = 210, .y = 320, .z = 0, .color = al_map_rgb_f(1, 0, 0) },
        { .x = 330, .y = 320, .z = 0, .color = al_map_rgb_f(0, 1, 0) },
        { .x = 210, .y = 420, .z = 0, .color = al_map_rgb_f(0, 0, 1) },
        { .x = 330, .y = 420, .z = 0, .color = al_map_rgb_f(1, 1, 0) },
        { .x = 270, .y = 470, .z = 0, .color = al_map_rgb_f(1, 0, 1) },
    };

    for (auto entity : entities_) {
        if (player_->get_z() == entity->get_z()) {
            int adjusted_x = entity->get_x() - player_->get_x() + (display_.get_width() / 2),
                adjusted_y = player_->get_y() - entity->get_y() + (display_.get_height() / 2),
                leeway = 30;

            if ( adjusted_x > -leeway 
                && adjusted_x < display_.get_width() + leeway
                && adjusted_y > -leeway
                && adjusted_y < display_.get_height() + leeway
            ) {
                entity->render(adjusted_x, adjusted_y - FONT_SIZE / 2);
            }
        }
    }

    al_draw_prim(v, NULL, NULL, 0, 5, ALLEGRO_PRIM_TRIANGLE_STRIP);
    
    al_flip_display();
}