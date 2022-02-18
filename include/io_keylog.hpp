#pragma once
#include <iostream>
#include <bitset>
#include <allegro5/allegro.h>

#define KEY_PRESSED  1
#define KEY_RELEASED 2

struct KeyLog {
    KeyLog() {
        // Set all the bits in the key_status_ array to 0:
        memset(key_status_, 0, sizeof(key_status_));
    }

    // Returns true if the key was pressed since the last frame.
    bool operator[](int keycode) const {
        return key_status_[keycode];
    }
    
    // Flags the key as 'has been pressed'.
    void set_key_pressed(int keycode) {
        key_status_[keycode] = KEY_PRESSED | KEY_RELEASED;
    }

    // Flags the key as 'has been released'.
    void set_key_released(int keycode) {
        key_status_[keycode] &= KEY_RELEASED;
    }

    // Flags the key as 'has been seen'. In other words, the key has been 
    // 'accounted for' or been through an input handler since being pressed.
    void set_key_seen(int keycode) {
        key_status_[keycode] &= KEY_PRESSED;
    }

    void print(int keycode) {
        std::cout << "keycode: " << keycode << "\n";
        std::cout << "status: " << std::bitset<8>(key_status_[keycode]) << "\n";
    }

    // Flags all known keys as 'has been seen'. In other words, all the keys have 
    // been 'accounted for' or been through an input handler since being pressed.
    void set_all_keys_seen() {
        for(int i = 1; i < ALLEGRO_KEY_MAX; i++)
            this->set_key_seen(i);
    }

private:
    /**
     * Chars in this array should only be one of these 4 values:
     * 00000011 ----> key pressed,      not released,    not seen
     * 00000001 ----> key pressed,      not released,    seen
     * 00000010 ----> key pressed,      released,        not seen
     * 00000000 ----> no input to process
     * 
     * "seen" ------> key has been through an input handler since being pressed
     * "pressed" ---> key was activated since last frame
     * "released" --> key was de-activated since last frame
     **/
    unsigned char key_status_[ALLEGRO_KEY_MAX];
}; // struct KeyLog

#undef KEY_SEEN
#undef KEY_RELEASED