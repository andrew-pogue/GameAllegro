#include "game.hpp"

void Game::load_test_player_fov()
{
    auto color = al_map_rgb(0, 255, 0);
    auto flag = ALLEGRO_ALIGN_CENTER;
    auto width = display_.get_width();
    auto height = display_.get_height();

    world_.entity("(0,0)")
        .set<CPosition>({0, 0, 0})
        .set<CText>({"(0,0)", color, flag})
        .set<CRender>({0, 0, 0});
    world_.entity("(+,+)")
        .set<CPosition>({width/2 - 8, height/2 - 8, 0})
        .set<CText>({"(+,+)", color, flag})
        .set<CRender>({0, 0, 0});
    world_.entity("(-,-)")
        .set<CPosition>({-width/2 + 8, -height/2 + 8, 0})
        .set<CText>({"(-,-)", color, flag})
        .set<CRender>({0, 0, 0});
    world_.entity("(+,0)")
        .set<CPosition>({width/2 - 8, 0, 0})
        .set<CText>({"(+,0)", color, flag})
        .set<CRender>({0, 0, 0});
    world_.entity("(-,0)")
        .set<CPosition>({-width/2 + 8, 0, 0})
        .set<CText>({"(-,0)", color, flag})
        .set<CRender>({0, 0, 0});
    world_.entity("(0,+)")
        .set<CPosition>({0, height/2 - 8, 0})
        .set<CText>({"(0,+)", color, flag})
        .set<CRender>({0, 0, 0});
    world_.entity("(0,-)")
        .set<CPosition>({0, -height/2 + 8, 0})
        .set<CText>({"(0,-)", color, flag})
        .set<CRender>({0, 0, 0});
    world_.entity("(+,-)")
        .set<CPosition>({width/2 - 8, -height/2 + 8, 0})
        .set<CText>({"(+,-)", color, flag})
        .set<CRender>({0, 0, 0});
    world_.entity("(-,+)")
        .set<CPosition>({-width/2 + 8, height/2 - 8, 0})
        .set<CText>({"(-,+)", color, flag})
        .set<CRender>({0, 0, 0});
}