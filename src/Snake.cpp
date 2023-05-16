//
// Created by dragosc1 on 21.04.2023.
//

// snake constructors
#include "../headers/Snake.h"

int Snake::score = 0;

Snake::Snake(const int &cellSize_, const std::vector <Cell> &body_) : cellSize(cellSize_) {
    reset(body_);
}

// reset snake
void Snake::reset(const std::vector <Cell> &body_) {
    body.clear();
    for (unsigned int i = 0; i < body_.size(); i++)
        body.push_back(body_[i]);
    setDirection(Direction::NONE); // snake direction is still
    // default snake values
    score = 0;
    speed = 1;
    speedTime = 1e9;
    invincibilityTime = 0;
    lost = false;
}

// snake direciton setter
void Snake::setDirection(const Direction &dir_) { dir = dir_; }

// snake lost
bool Snake::hasLost() { return lost; }

// snake body length
unsigned int Snake::bodyLength() { return body.size(); }

// snake get speed
float Snake::getSpeed() { return speed; }

// snake get position
Cell Snake::getPosition() { return body[0]; }

// get snake score
int Snake::getScore() { return score; }

// increase score
void Snake::increaseScore() { score++; }

// increase snake speed
void Snake::increaseSpeed() { speed *= 1.1; }

// snake has lost
void Snake::lose() { lost = true; }

// extend the snake
void Snake::extend() {
    const Cell &tailHead = body[body.size() - 1];
    const Cell &tailBone = body[body.size() - 2];
    if (tailHead.getX() == tailBone.getX()) {
        if (tailHead.getY() > tailBone.getY())
            body.push_back(Cell(tailHead.getX(), tailHead.getY() + 1));
        else body.push_back(Cell(tailHead.getX(), tailHead.getY() - 1));
    } else if (tailHead.getY() == tailBone.getY()) {
        if (tailHead.getX() > tailBone.getX())
            body.push_back(Cell(tailHead.getX() + 1, tailHead.getY()));
        else body.push_back(Cell(tailHead.getX() - 1, tailHead.getY()));
    }
}

// snake move
void Snake::move() {
    for (unsigned int i = body.size() - 1; i > 0; --i)
        body[i] = body[i - 1];
    if (dir == Direction::Left)
        body[0].setX(body[0].getX() - 1);
    else if (dir == Direction::Right)
        body[0].setX(body[0].getX() + 1);
    else if (dir == Direction::Up)
        body[0].setY(body[0].getY() - 1);
    else if (dir == Direction::Down)
        body[0].setY(body[0].getY() + 1);
}

// snake shorter by 1/3
void Snake::shorter() {
    // if the length is <= 2 it doesn't do anything
    for (unsigned int i = 0; i < body.size() / 3; i++)
        body.pop_back();
}

// snake activate invincibility
void Snake::activateInvincibility() {
    invincible = 1;
    invincibilityTime = 30;
}

bool Snake::isInvincible() { return invincible; }

// get physicial direction
Direction Snake::getPhysicalDirection() {
    const Cell &head = body[0];
    const Cell &neck = body[1];
    if (head.getX() == neck.getX()) { return (head.getY() > neck.getY() ? Direction::Down : Direction::Up); }
    else if (head.getY() == neck.getY()) { return (head.getX() > neck.getX() ? Direction::Right : Direction::Left); }
    return Direction::NONE;
}

// snake operator<<
std::ostream &operator<<(std::ostream &os, const Snake &snake) {
    os << "Snake cells:\n";
    for (const Cell &cell: snake.body) os << cell << '\n';
    os << "Snake speed: " << snake.speed << '\n';
    os << "Snake score: " << snake.score << "\n\n";
    return os;
}

// snake tick
void Snake::tick() {
    if (dir == Direction::NONE) { return; }
    speedTime--;
    if (speedTime == 0) {
        speed = 1;
        speedTime = 1e9;
    }
    move();
    if (!invincible)
        checkCollision();
    else {
        invincibilityTime--;
        if (invincibilityTime == 0)
            invincible = 0;
    }
}

// snake out of bounds
bool Snake::outOfBounds(const sf::Vector2u &windowSize) {
    int gridSize_x = windowSize.x / cellSize;
    int gridSize_y = windowSize.y / cellSize;
    return (body[0].getX() <= 0 || body[0].getY() <= 0 ||
            body[0].getX() >= (gridSize_x - 1) || body[0].getY() >= (gridSize_y - 1));
}

// snake check collision
void Snake::checkCollision() {
    if (body.size() < 5) { return; }
    Cell &head = body.front();
    for (auto itr = body.begin() + 1; itr != body.end(); ++itr)
        if (itr->position() == head.position()) {
            lose();
            break;
        }
}

// slow time
void Snake::slowTime() {
    speed = speed * 1.0 / 2;
    speedTime = 30;
}

// snake render
void Snake::render(sf::RenderWindow &window_) {
    auto head = body.begin();
    sf::RectangleShape bodyRect;
    bodyRect.setFillColor(D_GREEN);
    bodyRect.setPosition(head->getX() * cellSize, head->getY() * cellSize);
    bodyRect.setSize(sf::Vector2f(cellSize, cellSize));
    window_.draw(bodyRect);
    bodyRect.setFillColor(GREEN);
    for (auto itr = body.begin() + 1; itr != body.end(); ++itr) {
        bodyRect.setPosition(itr->getX() * cellSize, itr->getY() * cellSize);
        window_.draw(bodyRect);
    }
}
