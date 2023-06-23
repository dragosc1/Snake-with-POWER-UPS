//
// Created by dragosc1 on 23.06.2023.
//

#include "../headers/PowerUpFactory.h"

PowerUp* PowerUpFactory::create(int type, int x, int y, int cellSize) {
    if (type == SlowTimePowerUpType)
        return new SlowTimePowerUp({{x, y}, cellSize});
    else if (type == ShorterSnakePowerUpType)
        return new ShorterSnakePowerUp({{x, y}, cellSize});
    else if (type == InvincibilityPowerUpType)
        return new InvincibilityPowerUp({{x, y}, cellSize});
    return new FasterTimePowerUp({{x, y}, cellSize});
}