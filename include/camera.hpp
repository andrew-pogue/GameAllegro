#pragma once
#include "entity.hpp"

struct Camera : Entity {
    // marks this camera as the player's camera
    bool active; // only allow one active instance? up to 4 active instances for splitscreen coop?

    Camera(int x, int y, int z) : Entity(x, y, z) 
    { this->active = false; }

    // public so that NPCs can use it in 3D games?
    bool can_see(const Entity& entity) const {
    }

    // renders all entities within the camera's field of view
    void render() const {
        // entity.render();  ???
    }
};