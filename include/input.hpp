#pragma once
#include <stdlib.h>
#include <bitset>
#include <allegro5/allegro5.h>

#define KEY_SEEN     1
#define KEY_RELEASED 2

struct InputHandler {
    InputHandler() {
        memset(keys_, 0, sizeof(keys_));
    }

    void key_pressed(int keycode) {
        keys_[keycode] = KEY_SEEN | KEY_RELEASED;
    }

    void key_released(int keycode) {
        keys_[keycode] &= KEY_RELEASED;
    }

    void key_seen(int keycode) {
        keys_[keycode] &= KEY_SEEN;
    }

    void key_seen_all() {
        for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
            this->key_seen(i);
    }

    bool operator[](int keycode) {
        return keys_[keycode];
    }

private:
    unsigned char keys_[ALLEGRO_KEY_MAX];
};

#undef KEY_SEEN
#undef KEY_RELEASED