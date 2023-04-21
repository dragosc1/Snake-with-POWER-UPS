//
// Created by dragosc1 on 21.04.2023.
//

#ifndef OOP_EXTERN_H
#define OOP_EXTERN_H
#include <SFML/Graphics.hpp>
#include <iostream>

// constants for colors
const sf::Color GREEN = sf::Color::Green;
const sf::Color D_GREEN = sf::Color(0, 195, 50);
const sf::Color BLACK = sf::Color::Black;
const sf::Color RED = sf::Color::Red;
const sf::Color WHITE = sf::Color::White;
const sf::Color LGRAY = sf::Color(100, 100, 100);
const sf::Color BLUE = sf::Color::Blue;

// directions for snake
enum class Direction {
    NONE,
    Up,
    Down,
    Left,
    Right
};

#endif //OOP_EXTERN_H
