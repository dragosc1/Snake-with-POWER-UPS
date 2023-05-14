//
// Created by dragosc1 on 14.05.2023.
//

#include "../headers/InvincibilityPowerUp.h"

//
// Created by dragosc1 on 03.05.2023.
//

InvincibilityPowerUp::InvincibilityPowerUp(const InvincibilityPowerUp &other) : PowerUp(other) {}

InvincibilityPowerUp& InvincibilityPowerUp::operator=(const InvincibilityPowerUp &other) {
    PowerUp& powerUp = *this;
    powerUp = other;
    return *this;
}

InvincibilityPowerUp::InvincibilityPowerUp(std::pair<std::pair<int, int>, int> x) : PowerUp(x) {
    shape.setFillColor(YELLOW);
    shape.setRadius(8);
}

InvincibilityPowerUp::~InvincibilityPowerUp() {

}

void InvincibilityPowerUp::render(sf::RenderWindow &window) {
    window.draw(shape);
}

void InvincibilityPowerUp::applyPowerUp(Snake &snake) {
    snake.activateInvincibility();
}

std::string InvincibilityPowerUp::displayType() {
    return "Slow Time";
}

// clone
InvincibilityPowerUp* InvincibilityPowerUp::clone() const {
    return new InvincibilityPowerUp(*this);
}

// InvincibilityPowerUp operator<<
std::ostream& operator<<(std::ostream& os, InvincibilityPowerUp &InP) {
    os << InP.displayType() << ": \t" << "X=" << InP.getPosition().getX() << "; " << "Y=" << InP.getPosition().getY() << '\n';
    return os;
}