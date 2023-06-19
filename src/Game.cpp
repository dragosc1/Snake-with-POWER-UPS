//
// Created by dragosc1 on 21.04.2023.
//
#include "../headers/Game.h"

template <typename T>
Game<T>& Game<T>::getGame() {
    static Game<T> gameInstance;
    return gameInstance;
}

// init score
template <typename T>
void Game<T>::initScore() {
    if (!font.loadFromFile("arial.ttf"))
        throw font_error();
    font.loadFromFile("arial.ttf");
    score.setFont(font);
    score.setString("Score: ");
    score.setPosition(sf::Vector2f(30, 20));
    score.setCharacterSize(20);
    score.setFillColor(WHITE);
}

// game draw score
template <typename T>
void Game<T>::drawScore() {
    score.setString("Score: " + std::to_string(world.getSnakeScore()));
    window.drawScore(score);
}

// game constructors
template <typename T>
Game<T>::Game() : world(sf::Vector2u(800, 600)), window() {
    initScore();
}

// game operator<<
template <typename T>
std::ostream &operator<<(std::ostream &os, const Game<T> &game) {
    os << game.world << game.window << "Time spent: " << game.timespent << '\n' << "Time step: " << game.timestep
       << '\n';
    return os;
}

// render game
template <typename T>
void Game<T>::render() {
    window.beginDraw();
    drawScore();
    world.render(window.getWindow());
    world.renderSnake(window.getWindow());
    window.endDraw();
}

// handle the input
template <typename T>
void Game<T>::handleInput() {
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
template <typename T>
void Game<T>::update() {
    window.update(); // Update window events.
    if (timespent >= timestep) {
        world.update();
        if (world.snakeHasLost())
            world.reset();
        timespent = 0.0;
    } else timespent += world.getSnakeSpeed();
}

// game window not closed
template <typename T>
bool Game<T>::windowNotClosed() {
    return !window.isClosed();
}

// game destructor
template <typename T>
Game<T>::~Game() = default;

// declarations
template std::ostream& operator<<(std::ostream &, const Game<double> &);
template std::ostream& operator<<(std::ostream &, const Game<float> &);
template class Game<double>;
template class Game<float>;