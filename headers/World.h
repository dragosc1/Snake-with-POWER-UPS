//
// Created by dragosc1 on 21.04.2023.
//

#ifndef OOP_WORLD_H
#define OOP_WORLD_H
#include "Snake.h"
#include "PowerUp.h"
#include <vector>

// The World
class World {
private:
    // world data
    Snake snake;
    sf::RectangleShape bounds[4];
    sf::CircleShape fruitShape;
    sf::Vector2u windowSize;
    int cellSize = 16;
    Cell fruit;
//    std::vector<PowerUp*> powerUps;

    // init bounds
    void initBounds();

    // generate random snake of length 3
    std::vector<Cell> randomSnakeLength3();

    // cleanUp powerUps
    void cleanUp();

    // world swap
    friend void swap(World &, World &);

    // snake tick
    void tickSnake();

    // fruit random position
    void setRandomFruitPosition();

    // powerup random position
    void setRandomPowerUp();

    // reset snake
    void resetSnake();

public:

    // world constructors
    explicit World(const sf::Vector2u&);
    World(const World& );

    // world operator=
    World& operator= (World );

    // world operator<<
    friend std::ostream& operator<<(std::ostream& , const World& );

    // window render bounds
    void render(sf::RenderWindow &);

    // render snake
    void renderSnake(sf::RenderWindow &);

    // update snake
    void update();

    // world reset
    void reset();

    // get snake score
    int getSnakeScore();

    // snake has lost
    bool snakeHasLost();

    // get the snake's speed
    float getSnakeSpeed();

    // update snake direction
    void updateSnakeDirection(const Direction &);

    // world destructor
    ~World();
};

#endif //OOP_WORLD_H
