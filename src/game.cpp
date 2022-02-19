#include "game.hpp"

static const bool DEBUG = true;

Game::Game(std::string font_path, int font_size)
    : display_(WINDOW_WIDTH, WINDOW_HEIGHT), frame_timer_(1.0 / 30.0),
        event_queue_(), keylog_(), font_manager_(), player_(nullptr), entities_(),
        font_(font_path), font_size_(font_size)
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

    if (!font_manager_.load_ttf(font_, font_size_)) {
        throw "Failed to load font\"" + font_ + "\"";
    }

    Font font(font_manager_[font_], al_map_rgb(255, 255, 255));

    entities_.push_front(new entity::Text("@", Coord(0, 0, 0), font));
    player_ = entities_.front();

    load_test_unicode_font();
    // load_test_player_fov();
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

void Game::load_test_player_fov() {
    Font font(font_manager_[font_], al_map_rgb(0, 255, 0), ALLEGRO_ALIGN_CENTER);
    entities_.push_front(new entity::Text("(0,0)", Coord(0,          0,      0), font));
    entities_.push_front(new entity::Text("(+,+)", Coord(320 - 8,    240 - 8,    0), font));
    entities_.push_front(new entity::Text("(-,-)", Coord(-320 + 8,   -240 + 8,   0), font));
    entities_.push_front(new entity::Text("(+,0)", Coord(320 - 8,    0,         0), font));
    entities_.push_front(new entity::Text("(-,0)", Coord(-320 + 8,   0,         0), font));
    entities_.push_front(new entity::Text("(0,+)", Coord(0,          240 - 8,    0), font));
    entities_.push_front(new entity::Text("(0,-)", Coord(0,        -240 + 8,   0), font));
    entities_.push_front(new entity::Text("(+,-)", Coord(320 - 8,    -240 + 8,   0), font));
    entities_.push_front(new entity::Text("(-,+)", Coord(-320 + 8,   240 - 8,    0), font));
}

void Game::load_test_unicode_font() {
    ALLEGRO_FONT* font = font_manager_[font_];

    int ranges[] = {
        0x0000, 0x001F, /* Control 0 */
        0x0020, 0x007F, /* Base */
        0x0080, 0x009F, /* Control 1 */
        0x00A1, 0x00FF,  /* Latin 1 */
        0x0100, 0x017F,  /* Extended-A */
        0x0370, 0x03FF, /* Greek */
        0x2190, 0x21FF, /* Arrows */
        0x2500, 0x257F, /* Lines */
        0x2580, 0x259F, /* Blocks */
        0x25A0, 0x25FF, /* Shapes */
    };

    // int x = - display_.get_width(),
    //     y = - display_.get_height();

    int x = - WINDOW_WIDTH / 2 ,
        y = WINDOW_HEIGHT / 2;
    
    for (auto range = 0; range < 10; range++) {
        int start = ranges[2 * range];
        int stop = ranges[2 * range + 1];

        if (range > 0) {
            x = - WINDOW_WIDTH / 2;
            y -= font_size_ * 3;            
        }

        switch (range) {
        case 0:
            entities_.push_front(new entity::Text("Control 0: ", Coord(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 1:
            entities_.push_front(new entity::Text("ASCII: ", Coord(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 2:
            entities_.push_front(new entity::Text("Control 1: ", Coord(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 3:
            entities_.push_front(new entity::Text("Latin 1: ", Coord(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 4:
            entities_.push_front(new entity::Text("Extended-A: ", Coord(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 5:
            entities_.push_front(new entity::Text("Greek: ", Coord(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 6:
            entities_.push_front(new entity::Text("Arrows: ", Coord(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 7:
            entities_.push_front(new entity::Text("Lines: ", Coord(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 8:
            entities_.push_front(new entity::Text("Blocks: ", Coord(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 9:
            entities_.push_front(new entity::Text("Shapes: ", Coord(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        }

        for (auto i = start; i <= stop; i++) {
            int width = al_get_glyph_advance(font, i, ALLEGRO_NO_KERNING),
                r = fabs(sin(ALLEGRO_PI * (i) * 36 /360.0)) * 255.0,
                g = fabs(sin(ALLEGRO_PI * (i + 12) * 36 /360.0)) * 255.0,
                b = fabs(sin(ALLEGRO_PI * (i + 24) * 36 /360.0)) * 255.0;
            entities_.push_front(new entity::Glyph(i, Coord(x, y, 0), Font(font, al_map_rgb(r,g,b))));
            // al_draw_glyph(font, al_map_rgb(r,g,b), x, y, i);
            x += width * 2;
            if (x > WINDOW_WIDTH / 2) {
                x = - WINDOW_WIDTH / 2;
                y -= font_size_ * 2;
            }
        }
    }
}

/**
 * Renders all entities such that only entities that are visible on screen are rendered.
 **/
void Game::render() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_hold_bitmap_drawing(true);

    // ALLEGRO_VERTEX v[] = {
    //     { .x = 210, .y = 320, .z = 0, .color = al_map_rgb_f(1, 0, 0) },
    //     { .x = 330, .y = 320, .z = 0, .color = al_map_rgb_f(0, 1, 0) },
    //     { .x = 210, .y = 420, .z = 0, .color = al_map_rgb_f(0, 0, 1) },
    //     { .x = 330, .y = 420, .z = 0, .color = al_map_rgb_f(1, 1, 0) },
    //     { .x = 270, .y = 470, .z = 0, .color = al_map_rgb_f(1, 0, 1) },
    // };

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
                entity->render(adjusted_x, adjusted_y - font_size_ / 2);
            }
        }
    }

    // al_draw_prim(v, NULL, NULL, 0, 5, ALLEGRO_PRIM_TRIANGLE_STRIP);
    
    al_hold_bitmap_drawing(false);   
    al_flip_display();
}