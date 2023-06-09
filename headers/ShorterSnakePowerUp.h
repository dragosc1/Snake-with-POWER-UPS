//
// Created by dragosc1 on 05.05.2023.
//

#ifndef OOP_SHORTERSNAKEPOWERUP_H
#define OOP_SHORTERSNAKEPOWERUP_H
#include "PowerUp.h"

class ShorterSnakePowerUp : public PowerUp {
public:
    ShorterSnakePowerUp(const ShorterSnakePowerUp& );
    ShorterSnakePowerUp& operator=(const ShorterSnakePowerUp& );
    explicit ShorterSnakePowerUp(std::pair<std::pair<int, int>, int> );
    ~ShorterSnakePowerUp();
    void render(sf::RenderWindow &) override;
    void applyPowerUp(Snake& ) override;
    std::string displayType() override;
    ShorterSnakePowerUp* clone() const override;
};


#endif //OOP_SHORTERSNAKEPOWERUP_H
