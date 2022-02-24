#include "game.hpp"

void Game::load_text_systems() {
}

void Game::load_glyph_systems() {
}

void Game::load_move_systems() {
    world_.system<CMove, CPosition>("update_move()")
        .each([this](flecs::entity e, CMove& move, CPosition& pos) {
            move.in_progress = false;

            if (move.x) {
                move.in_progress = true;
                float i = 0.25 * move.x / std::abs(move.x);
                pos.x += i;
                move.x -= i;
            }
            
            if (move.y) {
                move.in_progress = true;
                float i = 0.25 * move.y / std::abs(move.y);
                pos.y += i;
                move.y -= i;
            }

            if (move.z) {
                move.in_progress = true;
                int i = move.z / std::abs(move.z);
                pos.z += i;
                move.z -= i;
            }

            if (!move.in_progress && move.cooldown) {
                move.in_progress = true;
                move.cooldown--;
            }
        });
}
