//
// Created by dragosc1 on 03.05.2023.
//

#include "../headers/SlowTimePowerUp.h"

SlowTimePowerUp::SlowTimePowerUp(const SlowTimePowerUp &other) : PowerUp(other) {}

SlowTimePowerUp& SlowTimePowerUp::operator=(const SlowTimePowerUp &other) {
    PowerUp& powerUp = *this;
    powerUp = other;

    return *this;
}

SlowTimePowerUp::SlowTimePowerUp(std::pair<std::pair<int, int>, int> x) : PowerUp(x) {
    shape.setFillColor(BLUE);
    shape.setRadius(8);
}

SlowTimePowerUp::~SlowTimePowerUp() {

}

void SlowTimePowerUp::render(sf::RenderWindow &window) {
    window.draw(shape);
}

void SlowTimePowerUp::applyPowerUp(Snake &snake) {
    snake.affectTime("half");
}

std::string SlowTimePowerUp::displayType() {
    return "Slow Time";
}

// clone
SlowTimePowerUp* SlowTimePowerUp::clone() const {
    return new SlowTimePowerUp(*this);
}

// slowTimePowerUp operator<<
std::ostream& operator<<(std::ostream& os, SlowTimePowerUp &STP) {
    os << STP.displayType() << ": \t" << "X=" << STP.getPosition().getX() << "; " << "Y=" << STP.getPosition().getY() << '\n';
    return os;
}