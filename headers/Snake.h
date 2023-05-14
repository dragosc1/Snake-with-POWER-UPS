//
// Created by dragosc1 on 21.04.2023.
//

#ifndef OOP_SNAKE_H
#define OOP_SNAKE_H
#include "extern.h"
#include "Cell.h"

// The snake
class Snake {
private:
    // snake data
    std::vector<Cell> body;
    double speed;
    static int score;
    int speedTime, invincibilityTime;
    bool lost, invincible;
    Direction dir;
    int cellSize;
public:
    // snake constructors
    explicit Snake(const int& , const std::vector<Cell> &);
    // reset snake
    void reset(const std::vector<Cell> &);

    // snake direction setter
    void setDirection(const Direction &);

    // snake lost
    bool hasLost();

    // snake get speed
    float getSpeed();

    // snake get position
    Cell getPosition();

    // get snake score
    static int getScore();

    // increase score
    static void increaseScore();

    // increase snake speed
    void increaseSpeed();

    // snake has lost
    void lose();

    // extend the snake
    void extend();

    // snake move
    void move();

    // snake shorter by 1/3
    void shorter();

    // snake activate invincibility
    void activateInvincibility();

    // get physicial direction
    Direction getPhysicalDirection();

    // snake operator<<
    friend std::ostream& operator<<(std::ostream& , const Snake&);

    // snake tick
    void tick();

    // snake out of bounds
    bool outOfBounds(const sf::Vector2u &);

    // snake check collision
    void checkCollision();

    // slow time
    void slowTime();

    // snake render
    void render(sf::RenderWindow &);
};

#endif //OOP_SNAKE_H
