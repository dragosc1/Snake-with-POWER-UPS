//
// Created by dragosc1 on 03.05.2023.
//

#ifndef OOP_SLOWTIMEPOWERUP_H
#define OOP_SLOWTIMEPOWERUP_H

#include "PowerUp.h"
#include "SFML/Graphics.hpp"

class SlowTimePowerUp : public PowerUp {
public:
    SlowTimePowerUp(std::pair<std::pair<int, int>, int> );
    ~SlowTimePowerUp();
    void render(sf::RenderWindow &) override;
    void applyPowerUp(Snake& ) override;
    std::string displayType() override;
};


#endif //OOP_SLOWTIMEPOWERUP_H
