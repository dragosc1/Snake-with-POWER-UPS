//
// Created by dragosc1 on 21.04.2023.
//

#ifndef OOP_WORLD_H
#define OOP_WORLD_H
#include "Snake.h"
#include "PowerUp.h"

// The World
class World {
private:
    // world data
    Snake snake;
    sf::RectangleShape bounds[4];
    sf::CircleShape fruitShape;
    sf::Vector2u windowSize;
    int cellSize;
    Cell fruit;
    std::vector<PowerUp*> powerUps;

    // init bounds
    void initBounds();

    // generate random snake of length 3
    std::vector<Cell> randomSnakeLength3();

public:
    // world constructors
    explicit World(const sf::Vector2u&);

    // world operator=
    World& operator= (World );

    // world swap
    friend void swap(World &, World &);

    // fruit random position
    void setRandomFruitPosition();

    // powerup random position
    void setRandomPowerUp();

    // world operator<<
    friend std::ostream& operator<<(std::ostream& , const World& );

    // window render bounds
    void render(sf::RenderWindow &);
    // render snake
    void renderSnake(sf::RenderWindow &);

    // update snake
    void update();

    // snake tick
    void tickSnake();

    // snake has lost
    bool snakeHasLost();

    // get the snake's speed
    float getSnakeSpeed();

    int getSnakeScore();

    // reset snake
    void resetSnake();

    // update snake direction
    void updateSnakeDirection(const Direction &);

    // world destructor
    ~World();
};

#endif //OOP_WORLD_H
