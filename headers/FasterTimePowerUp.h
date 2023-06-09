//
// Created by dragosc1 on 09.06.2023.
//

#ifndef OOP_FASTERTIMEPOWERUP_H
#define OOP_FASTERTIMEPOWERUP_H

#include "PowerUp.h"

class FasterTimePowerUp : public PowerUp {
public:
    FasterTimePowerUp(const FasterTimePowerUp& );
    FasterTimePowerUp& operator=(const FasterTimePowerUp& );
    explicit FasterTimePowerUp(std::pair<std::pair<int, int>, int> );
    ~FasterTimePowerUp();
    void render(sf::RenderWindow &) override;
    void applyPowerUp(Snake& ) override;
    std::string displayType() override;
    FasterTimePowerUp* clone() const override;
};



#endif //OOP_FASTERTIMEPOWERUP_H
