#include "headers/Game.h"

int main() {
    srand(time(nullptr));
    Game game;
    std::cout << "GAME INFO:\n\n";
    std::cout << game;
    while (game.windowNotClosed()) {
        game.handleInput();
        game.update();
        game.render();
    }
    return 1;
}
