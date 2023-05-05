//
// Created by dragosc1 on 03.05.2023.
//

#include "../headers/PowerUp.h"

int PowerUp::powerups = 0;

PowerUp::PowerUp(std::pair<std::pair<int, int>, int> x) {
    powerups++;
    std::pair<int, int> pos = x.first;
    int cellSize = x.second;
    position = Cell(pos.first, pos.second);
    shape.setPosition(position.getX() * cellSize, position.getY() * cellSize);
}

Cell PowerUp::getPosition() {
    return position;
}

PowerUp::~PowerUp() { powerups--; }
