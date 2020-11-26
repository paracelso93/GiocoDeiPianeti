#include "Game.h"

int main() {
    Game game;

    game.setup();

    while(!game.getClose()) {
        game.getInput();
        game.update();
        game.render();
    }

    game.clear();
    return 0;
}
