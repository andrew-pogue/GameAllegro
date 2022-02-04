#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

// too much abstraction?
// overcomplicating things?

/**
 * Abstract class for Allegro C++ wrappers that ensures Allegro's systems
 * are initialized before they are used.
 **/
struct Init {
    /**
     * Initializes Allegro core and sub-systems and installs input devices
     *  if they have not already been initialized/installed. If they have, does nothing.
     **/
    Init() {
        // if (DEBUG) printf("Game::init()\n");
        if (is_init_) return;

        if (!al_init())
            throw "Error: failed to initialize Allegro.";
        if (!al_init_font_addon())
            throw "Error: failed to initialize Allegro font addon.";
        if (!al_install_keyboard())
            throw "Error: failed to install keyboard.";
        if (!al_install_mouse())
            throw "Error: failed to install mouse.";

        is_init_ = true;
        printf("Allegro was initialized.\n");
    }

    virtual ~Init() {}

private:
    static inline bool is_init_ = false;
};