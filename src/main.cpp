#include <allegro5/allegro.h>
#include <stdio.h>
#include "game.hpp"

int main (int argc, char **argv) {
    Game* game;

    if (!Game::init()) {
        printf("Error: failed to initialize Allegro!\n");
        delete game;
        return 1;
    }

    try {
        game = new Game();
        game->play();
    }

    catch (const char * error) {
        for (int i = 0; error[i] != '\0'; i++)
            printf("%c", error[i]);
        printf("\nPress any key to continue...\n");
        getchar();
        delete game;
        return 1;
    }

    delete game;
    return 0;
}
