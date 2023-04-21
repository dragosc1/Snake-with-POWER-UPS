//
// Created by dragosc1 on 21.04.2023.
//

#ifndef OOP_WORLD_H
#define OOP_WORLD_H
#include "Snake.h"
// The World
class World {
private:
    // world data
    Snake snake;
    sf::CircleShape slowTimeShape;
    Cell slowTime;
    sf::RectangleShape bounds[4];
    sf::CircleShape fruitShape;
    sf::Vector2u windowSize;
    int cellSize;
    Cell fruit;

    // init bounds
    void initBounds();

    std::vector<Cell> randomSnakeLength3();

public:
    // world constructors
    explicit World(const sf::Vector2u&);

    // fruit random position
    void setRandomFruitPosition();

    // fruit random position
    void setRandomSlowTimePosition();

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