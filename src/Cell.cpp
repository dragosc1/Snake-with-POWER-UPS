//
// Created by dragosc1 on 21.04.2023.
//

#include "../headers/Cell.h"

// cell constructor
Cell::Cell(int x_, int y_) : x(x_), y(y_) {}

// cell copy constructor
Cell::Cell(const Cell &other) : x(other.x), y(other.y) {}

// cell operator=
Cell& Cell::operator=(const Cell &other) {
    x = other.x;
    y = other.y;
    return *this;
}

// cell operator==
bool Cell::operator==(const Cell &other) const { return (x == other.x && y == other.y); }

std::pair<int, int> Cell::position() {
    return {x, y};
}

// cell getters
int Cell::getX() const { return x; }

int Cell::getY() const { return y; }

// cell setters
void Cell::setX(int x_) { x = x_; }

void Cell::setY(int y_) { y = y_; }

// cell destructor
Cell::~Cell() = default;

// cell operator<<
std::ostream& operator<<(std::ostream &os, const Cell &cell) {
    os << "Cell:\t" << "X=" << cell.x << "; Y=" << cell.y << '\n';
    return os;
}