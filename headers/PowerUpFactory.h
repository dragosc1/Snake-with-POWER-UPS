//
// Created by dragosc1 on 23.06.2023.
//

#ifndef OOP_POWERUPFACTORY_H
#define OOP_POWERUPFACTORY_H

#include "PowerUp.h"
#include "ShorterSnakePowerUp.h"
#include "FasterTimePowerUp.h"
#include "SlowTimePowerUp.h"
#include "InvincibilityPowerUp.h"

class PowerUpFactory  {
public:
    static PowerUp* create(int, int, int, int);
};


#endif //OOP_POWERUPFACTORY_H
