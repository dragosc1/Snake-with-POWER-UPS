//
// Created by dragosc1 on 05.05.2023.
//

#include "../headers/ShorterSnakePowerUp.h"

ShorterSnakePowerUp::ShorterSnakePowerUp(std::pair<std::pair<int, int>, int> x) : PowerUp(x) {
    shape.setFillColor(PURPLE);
    shape.setRadius(8);
}

ShorterSnakePowerUp::~ShorterSnakePowerUp() noexcept {

}
void ShorterSnakePowerUp::render(sf::RenderWindow &window) {
    window.draw(shape);
}

void ShorterSnakePowerUp::applyPowerUp(Snake &snake) {
    snake.shorter();
}

std::string ShorterSnakePowerUp::displayType() {
    return "Shorter Snake";
}