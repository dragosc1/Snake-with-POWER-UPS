//
// Created by dragosc1 on 21.04.2023.
//
#include "../headers/World.h"
#include "../headers/SlowTimePowerUp.h"
#include "../headers/ShorterSnakePowerUp.h"
#include "../headers/InvincibilityPowerUp.h"
#include "../headers/Exceptions.h"

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
std::vector <Cell> World::randomSnakeLength3(int cellSize_) {
    std::vector <Cell> body;
    int maxX = (windowSize.x / cellSize_) - 4;
    int maxY = (windowSize.y / cellSize_) - 4;
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

// cleanUp powerUps
void World::cleanUp() {
    for (unsigned int i = 0; i < powerUps.size(); i++)
        delete powerUps[i];
    powerUps.clear();
}

// world constructors
World::World(const sf::Vector2u &windowSize_) : snake(cellSize = 16, randomSnakeLength3(16)), windowSize(windowSize_) {
    powerUps.clear();
    fruitShape.setFillColor(RED);
    fruitShape.setRadius(8);
    setRandomFruitPosition();
    setRandomPowerUp();
    cellSize = 16;
    initBounds();
}

World::World(const World& other) : snake(other.snake), fruitShape(other.fruitShape), windowSize(other.windowSize), cellSize(other.cellSize), fruit(other.fruit) {
    for (int i = 0; i < 4; i++)
        bounds[i] = other.bounds[i];
    powerUps.clear();
    for (unsigned int i = 0; i < other.powerUps.size(); i++)
        powerUps.push_back(other.powerUps[i]->clone());
}

// world operator=
World& World::operator=(World other) {
    swap(*this, other);
    return *this;
}

void swap(World &world1, World &world2) {
    using std::swap;
    swap(world1.snake, world2.snake);
    swap(world1.fruit, world2.fruit);
    swap(world1.fruitShape, world2.fruitShape);
    swap(world1.windowSize, world2.windowSize);
    swap(world1.cellSize, world2.cellSize);
    swap(world1.bounds, world2.bounds);
    swap(world1.powerUps, world2.powerUps);
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
    int type = rand() % PowerUpCount;
    if (type == SlowTimePowerUpType) {
        PowerUp *powerUp = new SlowTimePowerUp({{x, y}, cellSize});
        powerUps.push_back(powerUp);
    }
    else if (type == ShorterSnakePowerUpType) {
        PowerUp *powerUp = new ShorterSnakePowerUp({{x, y}, cellSize});
        powerUps.push_back(powerUp);
    }
    else if (type == InvincibilityPowerUpType) {
        PowerUp *powerUp = new InvincibilityPowerUp({{x, y}, cellSize});
        powerUps.push_back(powerUp);
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
    for (PowerUp* powerUp : powerUps) {
        powerUp->render(window_);
        if (powerUp->displayType() == "Invincibility") {
            InvincibilityPowerUp* invPowerUp = static_cast<InvincibilityPowerUp*>(powerUp);
            if (invPowerUp)
                invPowerUp->displayTextInv(window_);
        }
    }
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
        if (snake.bodyLength() >= (windowSize.x - 2) * (windowSize.y - 2))
            throw snake_error();
        Snake::increaseScore();

        // if score become a multiple of 25, add a a new powerUp
        if (Snake::getScore() % 25 == 0)
            setRandomPowerUp();

        snake.increaseSpeed(0.1);
        setRandomFruitPosition();
    }
    if (snake.outOfBounds(windowSize))
        snake.lose();
    tickSnake();
}

void World::reset() {
    resetSnake();
    setRandomFruitPosition();
    setRandomPowerUp();
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
    std::vector <Cell> body_ = randomSnakeLength3(cellSize);
    cleanUp();
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
    cleanUp();
}
