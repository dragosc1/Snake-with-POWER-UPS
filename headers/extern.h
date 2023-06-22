//
// Created by dragosc1 on 21.04.2023.
//

#ifndef OOP_EXTERN_H
#define OOP_EXTERN_H
#include <SFML/Graphics.hpp>
#include <iostream>

// constants for colors
const sf::Color GREEN = sf::Color(0, 255, 0);
const sf::Color D_GREEN = sf::Color(0, 195, 50);
const sf::Color BLACK = sf::Color(0, 0, 0);
const sf::Color RED = sf::Color(255, 0, 0);
const sf::Color WHITE = sf::Color(255, 255, 255);
const sf::Color LGRAY = sf::Color(100, 100, 100);
const sf::Color BLUE = sf::Color(0, 0, 255);
const sf::Color PURPLE = sf::Color(100, 0, 100);
const sf::Color YELLOW = sf::Color(255, 255, 0);
const sf::Color PINK = sf::Color(255,182,193);

// directions for snake
enum class Direction {
    NONE,
    Up,
    Down,
    Left,
    Right
};

enum PowerUps {
    SlowTimePowerUpType,
    ShorterSnakePowerUpType,
    InvincibilityPowerUpType,
    FasterTimePowerUpType,
    PowerUpCount,
};

#endif //OOP_EXTERN_H
