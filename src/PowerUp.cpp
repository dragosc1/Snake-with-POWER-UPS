//
// Created by dragosc1 on 03.05.2023.
//

#include "../headers/PowerUp.h"

PowerUp::PowerUp() {
    position = Cell(0, 0);
}

PowerUp::PowerUp(const PowerUp &other) {
    position = other.position;
    shape = other.shape;
}

PowerUp::PowerUp(std::pair<std::pair<int, int>, int> x) {
    std::pair<int, int> pos = x.first;
    int cellSize = x.second;
    position = Cell(pos.first, pos.second);
    shape.setPosition(position.getX() * cellSize, position.getY() * cellSize);
}

Cell PowerUp::getPosition() {
    return position;
}

PowerUp::~PowerUp() {}

// PowerUp operator<<
std::ostream& operator<<(std::ostream& os, PowerUp *powerUp) {
    os << powerUp->displayType() << ": \t" << "X=" << powerUp->position.getX() << "; " << "Y=" << powerUp->position.getY() << '\n';
    return os;
}