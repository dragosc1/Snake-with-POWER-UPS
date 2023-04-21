//
// Created by dragosc1 on 21.04.2023.
//
// The game
// game data
#include "../headers/Game.h"
// init score
void Game::initScore() {
    font.loadFromFile("arial.ttf");
    score.setFont(font);
    score.setString("Score: ");
    score.setPosition(sf::Vector2f(700, 16));
    score.setCharacterSize(20);
    score.setFillColor(WHITE);
}

// game draw score
void Game::drawScore() {
    score.setString("Score: " + std::to_string(world.getSnakeScore()));
    window.drawScore(score);
}

// game constructors
Game::Game() : world(sf::Vector2u(800, 600)), window() {
    initScore();
}

// game operator<<
std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << game.world << game.window << "Time spent: " << game.timespent << '\n' << "Time step: " << game.timestep
       << '\n';
    return os;
}

// render game
void Game::render() {
    window.beginDraw();
    drawScore();
    world.render(window.getWindow());
    world.renderSnake(window.getWindow());
    window.endDraw();
}

// handle the input
void Game::handleInput() {
    window.update();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        world.updateSnakeDirection(Direction::Up);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        world.updateSnakeDirection(Direction::Down);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        world.updateSnakeDirection(Direction::Left);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        world.updateSnakeDirection(Direction::Right);
}

// game update
void Game::update() {
    window.update(); // Update window events.
    if (timespent >= timestep) {
        world.tickSnake();
        world.update();
        if (world.snakeHasLost()) {
            world.resetSnake();
            world.setRandomFruitPosition();
            world.setRandomSlowTimePosition();
        }
        timespent = 0.f;
    } else timespent += world.getSnakeSpeed();
}

// game window not closed
bool Game::windowNotClosed() {
    return !window.isClosed();
}

// game destructor
Game::~Game() = default;