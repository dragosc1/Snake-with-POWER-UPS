//
// Created by dragosc1 on 03.05.2023.
//

#ifndef OOP_POWERUP_H
#define OOP_POWERUP_H
#include "Cell.h"
#include "SFML/Graphics.hpp"
#include "Snake.h"

class PowerUp {
private:
    Cell position;
protected:
    sf::CircleShape shape;
public:
    PowerUp();
    PowerUp(const PowerUp& );
    PowerUp(std::pair<std::pair<int, int>, int> );
    virtual ~PowerUp();
    virtual void render(sf::RenderWindow& ) = 0;
    virtual void applyPowerUp(Snake& ) = 0;
    virtual std::string displayType() = 0;
    friend std::ostream& operator<<(std::ostream&, PowerUp*);
    virtual PowerUp* clone() const = 0;
    Cell getPosition();
};

#endif //OOP_POWERUP_H