#include "game.hpp"

static const bool DEBUG = true;

Game::Game(std::string font_path, int font_size)
    : world_(), display_(WINDOW_WIDTH, WINDOW_HEIGHT), frame_timer_(1.0 / 30.0),
        event_queue_(), keylog_(), font_manager_(), font_path_(font_path), 
        font_size_(font_size), tile_size_(font_size / (4/3)), action_wait_(ALLEGRO_KEY_MAX, 0),
        move_wait_(0), traveling_(false), travelQ_()
{
    if (DEBUG) printf("Game::Game()\n");
    event_queue_.register_event_source(al_get_keyboard_event_source());
    event_queue_.register_event_source(al_get_mouse_event_source());
    event_queue_.register_event_source(display_);
    event_queue_.register_event_source(frame_timer_);
    
    if (!font_manager_.load_ttf(font_path_, font_size_)) 
    { throw "Failed to load font\"" + font_path_ + "\""; }

    player_ = world_.entity("player")
        .set<CPosition>({0,0,0})
        .set<CGlyph>({'@', al_map_rgb(255,255,255)})
        .set<CTravel>({0,0,0})
        .add<CRender>();

    printf("tile size = %i\n", tile_size_);

    action_wait_.shrink_to_fit();
    
    load_game_systems();
    load();
}

Game::~Game() {
    if (DEBUG) { printf("Game::~Game()\n"); }
}

void Game::play() {
    if (DEBUG) printf("Game::play()\n");
    
    bool redraw = true;
    ALLEGRO_EVENT event;
    frame_timer_.start();
    
    do {
        event_queue_.wait_for_event(&event);
        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            process_input();
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            keylog_.set_key_pressed(event.keyboard.keycode);
            break;
        case ALLEGRO_EVENT_KEY_UP:
            keylog_.set_key_released(event.keyboard.keycode);
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            world_.quit();
            break;
        }

        if (redraw && event_queue_.is_empty()) {
            render();
            redraw = false;
        }

        // world_.deactivate_systems();
    } while(world_.progress(0));
}

void Game::load() {
    if (DEBUG) printf("Game::load()\n");

    load_glyph_systems();
    load_text_systems();
    load_move_systems();

    // load_test_player_fov();

    // foo();

    int size = 10 * 10;
    if (size % 2 == 0) size++;
    int x_start = - size,
        y_start = size,
        y_end = - size,
        x_end = size;
    
    for (auto x = x_start; x < x_end; x += tile_size_) {
        for (auto y = y_start; y > y_end; y -= tile_size_) {
            int b = (int)(fabs(y + x) * size) % 255;
            world_.entity()
                .set<CGlyph>({'.', al_map_rgb(x,y,b)})
                .set<CPosition>({x, y, 0})
                .add<CRender>();
        }
    }
}

/**
 * Loads the core game systems. The game won't play without these loaded.
 **/
void Game::load_game_systems() {
    // Make event that only happens when Position was set/changed
    // Check time complexity of set, if high, maybe use add instead
}

void Game::process_input() {
    // add support for case in which player doesn't have CTravel
    auto travel = player_.get<CTravel>();
    int x = travel->x, 
        y = travel->y, 
        z = travel->z;
    bool moved = false;

    // make so move wait speeds up if button is held down
    // make so glyph slides to next tile?
    // make so glyph leaves temporary trail behind it as it moves
    if (!traveling_) {

        if (keylog_[ALLEGRO_KEY_UP]) {
            y += tile_size_;
            moved = true;
        }

        if (keylog_[ALLEGRO_KEY_DOWN]) {
            y -= tile_size_;
            moved = true;
        }

        if (keylog_[ALLEGRO_KEY_RIGHT]) {
            x += tile_size_;
            moved = true;
        }

        if (keylog_[ALLEGRO_KEY_LEFT]) {
            x -= tile_size_;
            moved = true;
        }

    }

    if (keylog_[ALLEGRO_KEY_C] && !action_wait_[ALLEGRO_KEY_C]) {
        action_wait_[ALLEGRO_KEY_C] = GAME_SPEED;
        auto pos = player_.get<CPosition>();
        printf("%s position: (%i,%i,%i)\n",
            player_.name().c_str(), pos->x, pos->y, pos->z);
    }
    
    for(size_t key = 0; key < action_wait_.size(); key++) {
        if (action_wait_[key] > 0) {
            action_wait_[key]--;
        }
    }

    if (!travelQ_.empty()) {
        player_.set<CTravel>({
            travelQ_.front().x,
            travelQ_.front().y,
            travelQ_.front().z,
        });
        travelQ_.pop();
        if (moved) travelQ_.push(CTravel({ x, y, z }));
    } else {
        if (moved) player_.set<CTravel>({ x, y, z });
    }
    keylog_.set_all_keys_seen();
}

void Game::render() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_hold_bitmap_drawing(true);

    // To improve readability and in-case these values change mid-rendering:
    auto const viewpoint = player_.get<CPosition>();
    const auto width = display_.get_width();
    const auto height = display_.get_height();
    const auto font_path = font_path_;
    const auto font_size = font_size_;
    const auto tile_size = tile_size_;

    // make it so this bit only runs when the player or instance has moved.
    world_.each([=](flecs::entity e, const CPosition& pos, CRender& rend) {
        if (e == player_) {
            rend.x = width/2;
            rend.y = height/2;
            rend.z = pos.z;
            rend.is_enabled = true;
            return;
        }

        rend.is_enabled = false;
        rend.x = pos.x - viewpoint->x + (width / 2);
        rend.y = viewpoint->y - pos.y + (height / 2) - (font_size / 2);
        rend.z = pos.z;

        if (rend.z == viewpoint->z
            && rend.x > -tile_size
            && rend.x < width + tile_size
            && rend.y > -tile_size
            && rend.y < height + tile_size
        ) {
            rend.is_enabled = true;
        }
    });

    world_.each([=](flecs::entity entity, CText& text, CRender& rend) {
        if (!rend.is_enabled) return;
        al_draw_text(
            font_manager_[font_path],
            text.color,
            rend.x, rend.y,
            text.render_flag,
            text.string.c_str()
        ); 
    });

    world_.each([=](flecs::entity entity, CGlyph& glyph, CRender& rend) {
        if (!rend.is_enabled) return;
        al_draw_glyph(
            font_manager_[font_path],
            glyph.color,
            rend.x, rend.y,
            glyph.codepoint
        );
    });

    al_hold_bitmap_drawing(false);
    al_flip_display();
}