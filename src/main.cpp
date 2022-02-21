#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "game.hpp"

void must_init(bool test, const char *description) {
    if(test) return;
    printf("Failed to initialize %s!\n", description);
    printf("Main End\n");
    exit(1);
}

int main (int argc, char **argv) {
    printf("Main Start\n");

    must_init(al_init(), "Allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");
    must_init(al_init_font_addon(), "font addon");
    must_init(al_init_ttf_addon(), "ttf addon");
    must_init(al_init_image_addon(), "image addon");
    must_init(al_init_primitives_addon(), "primitives addon");

    std::string font_path = "assets/font/PressStart2P-Regular.ttf";
    int font_size = 16;
    for (auto i = 0; i < argc; i++) {
        switch (i) {
        case 1:
            font_path = argv[i];
            break;
        case 2:
            font_size = atoi(argv[i]);
            if (!font_size) font_size = 16;
        default:
            break;
        }
    }

    Game* game = nullptr;
    
    try {
        game = new Game(font_path, font_size);
        game->play();
    }

    catch(const char * error) {
        printf("%s\n", error);
        delete game;
        printf("Main End\n");
        return 1;
    }

    delete game;
    printf("Main End\n");
    return 0;
}
