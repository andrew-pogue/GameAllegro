#pragma once
#include "alcpp_display.hpp"
#include "entity.hpp"

inline void render_test(const Display& display, const Entity* entity) {
    int render_x = entity->get_x() - display.get_x();
    int render_y = entity->get_y() - display.get_y();

    if ( render_x >= 0
        && render_x < display.get_width()
        && render_y >= 0
        && render_y < display.get_height() )
    {
        entity->render(render_x, render_y);
    }
}