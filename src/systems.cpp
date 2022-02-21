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
}

