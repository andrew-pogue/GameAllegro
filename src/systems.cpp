#include "game.hpp"

void Game::load_text_systems() {
}

void Game::load_glyph_systems() {
}

void Game::load_move_systems() {
    world_.system<CMove, CPosition>("update_move()")
        .each([](flecs::entity e, CMove& move, CPosition& pos) {
            pos.x += move.x;
            pos.y += move.y;
            pos.z += move.z;
            move.x = 0;
            move.y = 0;
            move.z = 0;
        });

    world_.system<CTravel, CPosition>("update_travel()")
        .each([this](flecs::entity e, CTravel& travel, CPosition& pos) {
            traveling_ = false;

            if (travel.x) {
                traveling_ = true;
                int i = tile_size_ / 4 * travel.x / std::abs(travel.x);
                pos.x += i;
                travel.x -= i;
            }
            
            if (travel.y) {
                traveling_ = true;
                auto i = tile_size_ / 4 * travel.y / std::abs(travel.y);
                pos.y += i;
                travel.y -= i;
            }

            if (travel.z) {
                traveling_ = true;
                auto i = travel.z / std::abs(travel.z);
                pos.z += i;
                travel.z -= i;
            }
        });
}
