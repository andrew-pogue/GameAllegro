#include "game.hpp"

static const bool DEBUG = true;

Game::Game(std::string font_path, int font_size)
    : world_(), display_(WINDOW_WIDTH, WINDOW_HEIGHT), frame_timer_(1.0 / 30.0),
        event_queue_(), keylog_(), font_manager_(), font_path_(font_path), 
        font_size_(font_size), tile_size_(font_size * (3/2)), action_wait_(ALLEGRO_KEY_MAX, 0),
        move_wait_(0), traveling_(false), moveQ_()
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
        .add<CMove>()
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

    int size = 10;
    float x_start = - size / 2,
        x_end = - x_start,
        y_start = size / 2,
        y_end = - y_start;
    
    for (auto x = x_start; x <= x_end; x++) {
        for (auto y = y_start; y >= y_end; y--) {
            int b = (int)(fabs(y + x) * size) % 255;
            auto color = al_map_rgb(x,y,b);
            if (!y || !x) color = al_map_rgb(155,155,155);
            world_.entity()
                .set<CGlyph>({'.', color})
                .set<CPosition>({ x, y, 0 })
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
    // printf("process_input()\n");

    // add support for case in which player doesn't have CTravel
    auto move = player_.get<CMove>();
    auto pos = player_.get<CPosition>();

    // make so move wait speeds up if button is held down
    // make so glyph slides to next tile?
    // make so glyph leaves temporary trail behind it as it moves

    if (!move->in_progress) {
        float move_x = 0, move_y = 0;
        int move_z = 0;

        if (keylog_[ALLEGRO_KEY_UP]) {
            move_y++;
        }

        if (keylog_[ALLEGRO_KEY_DOWN]) {
            move_y--;
        }

        if (keylog_[ALLEGRO_KEY_RIGHT]) {
            move_x++;
        }

        if (keylog_[ALLEGRO_KEY_LEFT]) {
            move_x--;
        }

        player_.set<CMove>({ move_x, move_y, move_z, 1, true });
    }

    if (keylog_[ALLEGRO_KEY_C] && !action_wait_[ALLEGRO_KEY_C]) {
        action_wait_[ALLEGRO_KEY_C] = GAME_SPEED;
        printf("%s position: (%f,%f,%i)\n",
            player_.name().c_str(), pos->x, pos->y, pos->z);
    }

    if (keylog_[ALLEGRO_KEY_SPACE] && !action_wait_[ALLEGRO_KEY_SPACE]) {
        action_wait_[ALLEGRO_KEY_SPACE] = GAME_SPEED;
        world_.entity()
            .set<CPosition>({pos->x, pos->y, pos->z})
            .set<CGlyph>({'#', al_map_rgb(155,155,155)})
            .add<CRender>();
    }
    
    for(size_t key = 0; key < action_wait_.size(); key++) {
        if (action_wait_[key]) {
            action_wait_[key]--;
        }
    }

    keylog_.set_all_keys_seen();
}

void Game::render() {
    // printf("render()\n");
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_hold_bitmap_drawing(true);

    // To improve readability and in-case these values change mid-rendering:
    auto const viewpoint = player_.get<CPosition>();
    const auto width = display_.get_width();
    const auto height = display_.get_height();
    const auto font_path = font_path_;
    // const auto font_size = font_size_;
    const auto tile_size = tile_size_;

    // make it so this bit only runs when the player or instance has moved.
    world_.each([=](flecs::entity e, const CPosition& pos, CRender& rend) {
        if (e == player_) {
            rend.x = (float)width / 2;
            rend.y = (float)height / 2;
            rend.z = pos.z;
            rend.is_enabled = true;
            return;
        }

        rend.is_enabled = false;
        rend.x = (pos.x - viewpoint->x) * tile_size + (float)width / 2;
        rend.y = (viewpoint->y - pos.y) * tile_size + (float)height / 2;
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

    world_.each([=](flecs::entity entity, const CText& text, const CRender& rend) {
        if (!rend.is_enabled) return;
        al_draw_text(
            font_manager_[font_path],
            text.color,
            rend.x, rend.y,
            text.render_flag,
            text.string.c_str()
        ); 
    });

    world_.each([=](flecs::entity entity, const CGlyph& glyph, const CRender& rend) {
        if (!rend.is_enabled) return;
        float j = 0.0;
        if (glyph.codepoint == '.') j = (float)tile_size_ / 4.0;
        al_draw_glyph(
            font_manager_[font_path],
            glyph.color,
            rend.x, rend.y - j,
            glyph.codepoint
        );
    });

    al_hold_bitmap_drawing(false);
    al_flip_display();
}