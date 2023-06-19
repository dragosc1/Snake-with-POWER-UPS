#include "headers/Game.h"
#include <iostream>

int main() {
    srand(time(nullptr));
    try {
        // try different ticking methods with double / float
        auto &game = Game<float>::getGame();
        std::cout << "GAME INFO:\n\n";
        std::cout << game;
        while (game.windowNotClosed()) {
            game.handleInput();
            game.update();
            game.render();
        }
    }
    catch (std::logic_error &err) {
        std::cout << err.what();
    }
    catch (font_error &err) {
        std::cout << err.what();
    }
    catch (snake_error &err) {
        std::cout << err.what();
    }
    catch (application_error &err) {
        std::cout << err.what();
    }
    catch (...) {
        std::cout << "Unexpected error!\n";
    }
    return 0;
}
