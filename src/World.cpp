//
// Created by dragosc1 on 21.04.2023.
//
#include "../headers/World.h"
#include "../headers/SlowTimePowerUp.h"
#include "../headers/ShorterSnakePowerUp.h"

// init bounds
void World::initBounds() {
    for (int i = 0; i < 4; ++i) {
        bounds[i].setFillColor(LGRAY);
        if (((i + 1) & 1) == 0) {
            bounds[i].setSize(sf::Vector2f(windowSize.x, cellSize));
        } else bounds[i].setSize(sf::Vector2f(cellSize, windowSize.y));
        if (i < 2) bounds[i].setPosition(0, 0);
        else {
            bounds[i].setOrigin(bounds[i].getSize());
            bounds[i].setPosition(sf::Vector2f(windowSize));
        }
    }
}

// generate random snake of length 3
std::vector <Cell> World::randomSnakeLength3() {
    std::vector <Cell> body;
    int maxX = (windowSize.x / cellSize) - 4;
    int maxY = (windowSize.y / cellSize) - 4;
    int orientation = rand() % 2;
    int x = rand() % maxX + 5, y = rand() % maxY + 5;
    // row orientation
    if (orientation == 0) {
        body.push_back(Cell(x, y + 2));
        body.push_back(Cell(x, y + 1));
        body.push_back(Cell(x, y));
    }
    // column orientation
    else {
        body.push_back(Cell(x + 2, y));
        body.push_back(Cell(x + 1, y));
        body.push_back(Cell(x, y));
    }
    return body;
}

// world constructors
World::World(const sf::Vector2u &windowSize_) : snake(cellSize = 16, randomSnakeLength3()), windowSize(windowSize_) {
    powerUps.clear();
    fruitShape.setFillColor(RED);
    fruitShape.setRadius(8);
    setRandomFruitPosition();
    setRandomPowerUp();
    cellSize = 16;
    initBounds();
}

// fruit random position
void World::setRandomFruitPosition() {
    int maxX = (windowSize.x / cellSize) - 2;
    int maxY = (windowSize.y / cellSize) - 2;
    int x = rand() % maxX + 1;
    int y = rand() % maxY + 1;
    fruit = Cell(x, y);
    fruitShape.setPosition(sf::Vector2f(x * cellSize, y * cellSize));
}

// fruit random position
void World::setRandomPowerUp() {
    int maxX = (windowSize.x / cellSize) - 2;
    int maxY = (windowSize.y / cellSize) - 2;
    int x = rand() % maxX + 1;
    int y = rand() % maxY + 1;
    int type = rand() % 2;
    if (type == 0) {
        PowerUp *powerUp = new SlowTimePowerUp({{x, y}, cellSize});
        powerUps.push_back(powerUp->clone());
        delete powerUp;
    }
    else {
        PowerUp *powerUp = new ShorterSnakePowerUp({{x, y}, cellSize});
        powerUps.push_back(powerUp->clone());
        delete powerUp;
    }
}

// world operator<<
std::ostream &operator<<(std::ostream &os, const World &world) {
    os << world.snake << "Fruit:\t" << "X=" << world.fruitShape.getPosition().x << "; Y="
       << world.fruitShape.getPosition().y << '\n';
    os << "PowerUps available:\n";
    for (PowerUp *powerUp : world.powerUps)
        os << powerUp;
    os << "\n\n";
    os << "Cell size: " << world.cellSize << '\n';
    return os;
}

// window render bounds
void World::render(sf::RenderWindow &window_) {
    for (const auto & bound : bounds)
        window_.draw(bound);
    window_.draw(fruitShape);
    window_.draw(slowTimeShape);
    for (PowerUp* powerUp : powerUps)
        powerUp->render(window_);
}

// render snake
void World::renderSnake(sf::RenderWindow &window_) {
    snake.render(window_);
}

// update snake
void World::update() {
    for (unsigned int i = 0; i < powerUps.size(); i++)
        if (snake.getPosition() == powerUps[i]->getPosition()) {
            powerUps[i]->applyPowerUp(snake);
            delete powerUps[i];
            powerUps.erase(powerUps.begin() + i);
            setRandomPowerUp();
            break;
        }
    if (snake.getPosition() == fruit) {
        snake.extend();
        Snake::increaseScore();
        snake.increaseSpeed();
        setRandomFruitPosition();
    }
    if (snake.outOfBounds(windowSize))
        snake.lose();
}

// snake tick
void World::tickSnake() {
    snake.tick();
}

// snake has lost
bool World::snakeHasLost() {
    return snake.hasLost();
}

// get the snake's speed
float World::getSnakeSpeed() {
    return snake.getSpeed();
}

int World::getSnakeScore() {
    return snake.getScore();
}

// reset snake
void World::resetSnake() {
    std::vector <Cell> body_ = randomSnakeLength3();
    for (unsigned int i = 0; i < powerUps.size(); i++)
        delete powerUps[i];
    powerUps.clear();
    snake.reset(body_);
}

// update snake direction
void World::updateSnakeDirection(const Direction &dir) {
    if (dir == Direction::Up && snake.getPhysicalDirection() != Direction::Down)
        snake.setDirection(dir);
    else if (dir == Direction::Down && snake.getPhysicalDirection() != Direction::Up)
        snake.setDirection(dir);
    else if (dir == Direction::Left && snake.getPhysicalDirection() != Direction::Right)
        snake.setDirection(dir);
    else if (dir == Direction::Right && snake.getPhysicalDirection() != Direction::Left)
        snake.setDirection(dir);
}

// world destructor
World::~World() {
    for (int i = powerUps.size() - 1; i >= 0; i--)
        delete powerUps[i];
}
