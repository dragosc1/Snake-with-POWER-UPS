//
// Created by dragosc1 on 05.05.2023.
//

#include "../headers/ShorterSnakePowerUp.h"

ShorterSnakePowerUp::ShorterSnakePowerUp(const ShorterSnakePowerUp &other) : PowerUp(other) {}

ShorterSnakePowerUp& ShorterSnakePowerUp::operator=(const ShorterSnakePowerUp &other) {
    PowerUp& powerUp = *this;
    powerUp = other;

    return *this;
}

ShorterSnakePowerUp::ShorterSnakePowerUp(std::pair<std::pair<int, int>, int> x) : PowerUp(x) {
    shape.setFillColor(PURPLE);
    shape.setRadius(8);
}

ShorterSnakePowerUp::~ShorterSnakePowerUp() {

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

// clone
ShorterSnakePowerUp* ShorterSnakePowerUp::clone() const {
    return new ShorterSnakePowerUp(*this);
}

// shorterSnakePowerUp operator<<
std::ostream& operator<<(std::ostream& os, ShorterSnakePowerUp &SSP) {
    os << SSP.displayType() << ": \t" << "X=" << SSP.getPosition().getX() << "; " << "Y=" << SSP.getPosition().getY() << '\n';
    return os;
}