//
// Created by dragosc1 on 21.04.2023.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H
#include "World.h"
#include "GameWindow.h"
#include "Exceptions.h"
#include <ostream>

// The game
template<typename T>
class Game {
private:
    // game data
    World world;
    GameWindow &window;
    T timespent = 0, timestep = 10;
    sf::Text score;
    sf::Font font;

    // init score
    void initScore();

    // game draw score
    void drawScore();

public:
    // get game instance
    static Game& getGame();

    // game constructors
    Game();

    // game operator<<
    template<class TA>
    friend std::ostream& operator<<(std::ostream& , const Game<TA>& );

    // render game
    void render();

    // handle the input
    void handleInput();

    // game update
    void update();

    // game window not closed
    bool windowNotClosed();

    // game destructor
    ~Game();
};

#endif //OOP_GAME_H
