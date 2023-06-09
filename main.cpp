#include "headers/Game.h"
#include <iostream>

int main() {
    srand(time(nullptr));
    try {
        Game game;
        std::cout << "GAME INFO:\n\n";
        std::cout << game;
        while (game.windowNotClosed()) {
            game.handleInput();
            game.update();
            game.render();
        }
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
