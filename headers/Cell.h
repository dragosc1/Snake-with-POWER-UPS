//
// Created by dragosc1 on 21.04.2023.
//

#ifndef OOP_CELL_H
#define OOP_CELL_H
#include "extern.h"

// A cell on the screen
class Cell {
private:
    // cell data
    int x, y;
public:
    // cell constructor
    explicit Cell(int x_ = 0, int y_ = 0);

    // cell copy constructor
    Cell(const Cell&);

    // cell operator=
    Cell& operator= (const Cell&);

    // cell operator==
    bool operator== (const Cell&) const;

    std::pair<int, int> position();

    // cell getters
    int getX() const;
    int getY() const;

    // cell setters
    void setX(int);
    void setY(int);

    // cell destructor
    ~Cell();

    // cell operator<<
    friend std::ostream& operator<<(std::ostream&, const Cell&);
};

#endif //OOP_CELL_H
