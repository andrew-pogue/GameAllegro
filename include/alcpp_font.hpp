#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include "alcpp_init.hpp"

// Wrapper for ALLEGRO_FONT
struct Font : Init {
    Font();
    ~Font();

    operator ALLEGRO_FONT* ()
    { return font_; }

    operator const ALLEGRO_FONT* () const
    { return (const ALLEGRO_FONT*)font_; }
private:
    ALLEGRO_FONT* font_;
};