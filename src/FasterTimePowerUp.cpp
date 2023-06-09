//
// Created by dragosc1 on 09.06.2023.
//

#include "../headers/FasterTimePowerUp.h"

FasterTimePowerUp::FasterTimePowerUp(const FasterTimePowerUp &other) : PowerUp(other) {}

FasterTimePowerUp& FasterTimePowerUp::operator=(const FasterTimePowerUp &other) {
    PowerUp& powerUp = *this;
    powerUp = other;

    return *this;
}

FasterTimePowerUp::FasterTimePowerUp(std::pair<std::pair<int, int>, int> x) : PowerUp(x) {
    shape.setFillColor(PINK);
    shape.setRadius(8);
}

FasterTimePowerUp::~FasterTimePowerUp() {

}

void FasterTimePowerUp::render(sf::RenderWindow &window) {
    window.draw(shape);
}

void FasterTimePowerUp::applyPowerUp(Snake &snake) {
    snake.affectTime("double");
}

std::string FasterTimePowerUp::displayType() {
    return "Faster Time";
}

// clone
FasterTimePowerUp* FasterTimePowerUp::clone() const {
    return new FasterTimePowerUp(*this);
}

// slowTimePowerUp operator<<
std::ostream& operator<<(std::ostream& os, FasterTimePowerUp &STP) {
    os << STP.displayType() << ": \t" << "X=" << STP.getPosition().getX() << "; " << "Y=" << STP.getPosition().getY() << '\n';
    return os;
}