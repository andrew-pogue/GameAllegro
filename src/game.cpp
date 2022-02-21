#include "game.hpp"

static const bool DEBUG = true;

Game::Game(std::string font_path, int font_size)
    : world_(), display_(WINDOW_WIDTH, WINDOW_HEIGHT), frame_timer_(1.0 / 30.0),
        event_queue_(), keylog_(), font_manager_(), font_path_(font_path), 
        font_size_(font_size), tile_size_(font_size * 2), action_wait_(0)
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
        .set<CGlyph>({'@', al_map_rgb(255,255,255)});
    
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

    load_test_player_fov();

    // int size = 60 * 30;
    // int x_start = - size / 2,
    //     y_start = size / 2,
    //     y_end = - size / 2,
    //     x_end = size / 2;
    
    // for (auto x = x_start; x < x_end; x += 60) {
    //     for (auto y = y_start; y > y_end; y -= 60) {
    //         int b = (int)(fabs(y + x) * 16) % 255;
    //         printf("b = %i\n", b);
    //         font.color = al_map_rgb(x,y,b);
    //         entities_.push_front(new entity::Glyph('.', Coord(x, y, 0), font));
    //     }
    // }
}

/**
 * Loads the core game systems. The game won't play without these loaded.
 **/
void Game::load_game_systems() {
    // Make event that only happens when Position was set/changed
    // Check time complexity of set, if high, maybe use add instead
}

void Game::process_input() {
    int x = 0, y = 0, z = 0;

    if (keylog_[ALLEGRO_KEY_UP]) {
        y += tile_size_/2;
        action_wait_ = GAME_SPEED;
    }

    if (keylog_[ALLEGRO_KEY_DOWN]) {
        y -= tile_size_/2;
        action_wait_ = GAME_SPEED;
    }

    if (keylog_[ALLEGRO_KEY_RIGHT]) {
        x += tile_size_/2;
        action_wait_ = GAME_SPEED;
    }

    if (keylog_[ALLEGRO_KEY_LEFT]) {
        x -= tile_size_/2;
        action_wait_ = GAME_SPEED;
    }

    if (keylog_[ALLEGRO_KEY_C]) {
        auto pos = player_.get<CPosition>();
        printf("%s position: (%i,%i,%i)\n",
            player_.name().c_str(), pos->x, pos->y, pos->z);
        action_wait_ = GAME_SPEED;
    }

    player_.set<CMove>({ x, y, z });
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

    world_.each([=](flecs::entity e, const CPosition& pos, CRender& crender) {
        crender.is_enabled = false;
        crender.x = pos.x - viewpoint->x + (width / 2);
        crender.y = viewpoint->y - pos.y + (height / 2) - (font_size / 2);
        crender.z = pos.z;

        if (crender.z == viewpoint->z
            && crender.x > -tile_size
            && crender.x < width + tile_size
            && crender.y > -tile_size
            && crender.y < height + tile_size
        ) {
            crender.is_enabled = true;
        }
    });

    world_.each([=](flecs::entity entity, CText& text, CRender& crender) {
        // std::cout << "render_text(" << entity.name() << ")\n";
        // printf(" at (x = %i, y = %i, z = %i)\n", crender.x, crender.y, crender.z);
        al_draw_text(
            font_manager_[font_path],
            text.color,
            crender.x, crender.y,
            text.render_flag,
            text.string.c_str()
        ); 
    });

    world_.each([=](flecs::entity entity, CGlyph& glyph, CRender& crender) {
        // std::cout << "render_glyph(" << entity.id() << ")";
        // printf(" at (x = %i, y = %i, z = %i)\n", crender.x, crender.y, crender.z);
        al_draw_glyph(
            font_manager_[font_path],
            glyph.color,
            crender.x, crender.y,
            glyph.codepoint
        );
    });

    // there is a better way to render the player
    if (player_.has<CGlyph>()) {
        auto glyph = player_.get<CGlyph>();
        al_draw_glyph(
            font_manager_[font_path],
            glyph->color,
            width / 2, height / 2,
            glyph->codepoint
        );
    }

    al_hold_bitmap_drawing(false);
    al_flip_display();
}