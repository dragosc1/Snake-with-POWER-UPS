//
// Created by dragosc1 on 21.04.2023.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H
#include "World.h"
#include "GameWindow.h"

// The game
class Game {
private:
    // game data
    World world;
    GameWindow window;
    float timespent = 0, timestep = 10;
    sf::Text score;
    sf::Font font;

    // init score
    void initScore();

    // game draw score
    void drawScore();

public:
    // game constructors
    Game();

    // game operator<<
    friend std::ostream& operator<<(std::ostream& , const Game& );

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
