//
// Created by dragosc1 on 14.05.2023.
//

#ifndef OOP_INVINCIBILITYPOWERUP_H
#define OOP_INVINCIBILITYPOWERUP_H
#include "PowerUp.h"

class InvincibilityPowerUp : public PowerUp {
public:
    InvincibilityPowerUp(const InvincibilityPowerUp& );
    InvincibilityPowerUp& operator=(const InvincibilityPowerUp& );
    explicit InvincibilityPowerUp(std::pair<std::pair<int, int>, int> );
    ~InvincibilityPowerUp();
    void render(sf::RenderWindow &) override;
    void applyPowerUp(Snake& ) override;
    std::string displayType() override;
    InvincibilityPowerUp* clone() const override;
    void displayTextInv(sf::RenderWindow &);
};


#endif //OOP_INVINCIBILITYPOWERUP_H
