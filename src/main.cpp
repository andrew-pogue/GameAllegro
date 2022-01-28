#include <allegro5/allegro.h>
#include "game.hpp"

int main (int argc, char **argv) {

    Game* game;
    try {
        game = new Game();
        game->play();
    }
    
    catch (const char * error) {
        for (int i = 0; error[i] != '\0'; i++) {
            std::cout << error[i];
        }
        std::cout << "\nPress any key to continue...\n";
        getchar();
        delete game;
        return 1;
    }

    delete game;
    return 0;
}