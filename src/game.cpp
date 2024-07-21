#include "game.hpp"

static const bool DEBUG = true;

Game::Game(std::string font_path, int font_size)
    : display_(WINDOW_WIDTH, WINDOW_HEIGHT), frame_timer_(1.0 / 30.0),
        event_queue_(), keylog_(), font_manager_(), font_path_(font_path),
        font_size_(font_size), player_(nullptr), tile_list_()
{
    if (DEBUG) printf("Game::Game()\n");
    event_queue_.register_source(al_get_keyboard_event_source());
    event_queue_.register_source(al_get_mouse_event_source());
    event_queue_.register_source(display_);
    event_queue_.register_source(frame_timer_);
    load();
}

Game::~Game() {
    if (DEBUG) { printf("Game::~Game()\n"); }
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

        update();

        if (redraw && event_queue_.is_empty()) {
            render();
            redraw = false;
        }
    }
}

void Game::load() {
    if (DEBUG) printf("Game::load()\n");

    if (!font_manager_.load_ttf(font_path_, font_size_)) {
        throw "Failed to load font \"" + font_path_ + "\"";
    }

    tile_list_.push_front({0,0,0});
    tile_list_.front().add(new Glyph('@'));

    // load_test_unicode_font();
    // load_test_player_fov();
}

void Game::handle_input() {

    // if (DEBUG) printf("Game::handle_input(ALLEGRO_EVENT)\n");
    if (keylog_[ALLEGRO_KEY_UP]) {
        player_->act(Move({})))
         player_-> move(0,PLAYER_SPEED,0);
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
    auto font = font_manager_[font_path_];
    auto color = al_map_rgb(0, 255, 0);
    auto flag = ALLEGRO_ALIGN_CENTER;
    int i = display_.get_width() / 2 - Tile::size,
        j = display_.get_height() / 2 - Tile::size;
    tiles_.
    tiles_[0][0][0].add(new Text("(0,0)", font, color, flag));
    tiles_[i][j][0].add(new Text("(+,+)", font, color, flag));
    tiles_[-i][-j][0].add(new Text("(-,-)", font, color, flag));
    tiles_[i][0][0].add(new Text("(+,0)", font, color, flag));
    tiles_[-i][0][0].add(new Text("(-,0)", font, color, flag));
    tiles_[0][j][0].add(new Text("(0,+)", font, color, flag));
    tiles_[0][-j][0].add(new Text("(0,-)", font, color, flag));
    tiles_[i][-j][0].add(new Text("(+,-)", font, color, flag));
    tiles_[-i][j][0].add(new Text("(-,+)", font, color, flag));
}

void Game::load_test_unicode_font() {
    ALLEGRO_FONT* font = font_manager_[font_path_];

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
            entities_.push_front(new entity::Text("Control 0: ", Position(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 1:
            entities_.push_front(new entity::Text("ASCII: ", Position(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 2:
            entities_.push_front(new entity::Text("Control 1: ", Position(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 3:
            entities_.push_front(new entity::Text("Latin 1: ", Position(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 4:
            entities_.push_front(new entity::Text("Extended-A: ", Position(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 5:
            entities_.push_front(new entity::Text("Greek: ", Position(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 6:
            entities_.push_front(new entity::Text("Arrows: ", Position(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 7:
            entities_.push_front(new entity::Text("Lines: ", Position(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 8:
            entities_.push_front(new entity::Text("Blocks: ", Position(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        case 9:
            entities_.push_front(new entity::Text("Shapes: ", Position(x - 275, y, 0),
                Font(font, al_map_rgb(255,255,255), ALLEGRO_ALIGN_LEFT)));
            break;
        }

        for (auto i = start; i <= stop; i++) {
            int width = al_get_glyph_advance(font, i, ALLEGRO_NO_KERNING),
                r = fabs(sin(ALLEGRO_PI * (i) * 36 /360.0)) * 255.0,
                g = fabs(sin(ALLEGRO_PI * (i + 12) * 36 /360.0)) * 255.0,
                b = fabs(sin(ALLEGRO_PI * (i + 24) * 36 /360.0)) * 255.0;
            entities_.push_front(new entity::Glyph(i, Position(x, y, 0), Font(font, al_map_rgb(r,g,b))));
            // al_draw_glyph(font, al_map_rgb(r,g,b), x, y, i);
            x += width * 2;
            if (x > WINDOW_WIDTH / 2) {
                x = - WINDOW_WIDTH / 2;
                y -= font_size_ * 2;
            }
        }
    }
}

void Game::update() {
    for (auto tile : tile_list_) tile.update();
}

/**
 * Renders all entities such that only entities that are visible on screen are rendered.
 **/
void Game::render() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_hold_bitmap_drawing(true);

    for (auto tile : tile_list_) render(tile);
    
    al_hold_bitmap_drawing(false);   
    al_flip_display();
}

void Game::render(const Tile& tile) const {
    if (player_->tile->z != tile.z) return;

    int display_width = display_.get_width(),
        display_height = display_.get_height();
    Tile::size = font_size_ * 5.0 / 4.0;

    const float adjusted_x = (tile.x - player_->x) * Tile::size + (float)display_width / 2,
        adjusted_y = (player_->y - tile.y) * Tile::size + (float)display_height / 2;

    if ( adjusted_x > -Tile::size
        && adjusted_x < display_width + Tile::size
        && adjusted_y > -Tile::size
        && adjusted_y < display_height + Tile::size
    ) {
        tile.render(adjusted_x, adjusted_y);
    }
}