//
// Created by dragosc1 on 03.05.2023.
//

#include "../headers/SlowTimePowerUp.h"

SlowTimePowerUp::SlowTimePowerUp(std::pair<std::pair<int, int>, int> x) : PowerUp(x) {
    shape.setFillColor(BLUE);
    shape.setRadius(8);
}

SlowTimePowerUp::~SlowTimePowerUp() noexcept {

}

void SlowTimePowerUp::render(sf::RenderWindow &window) {
    window.draw(shape);
}

void SlowTimePowerUp::applyPowerUp(Snake &snake) {
    snake.slowTime();
}

std::string SlowTimePowerUp::displayType() {
    return "Slow Time";
}