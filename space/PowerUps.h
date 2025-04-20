#ifndef POWERUP_H
#define POWERUP_H

#include "Enemy.h"
#include "Player.h"

class PowerUp : public Enemy
{
private:
    void initTexture();  // Override to use a different texture

public:
    PowerUp(float pos_x, float pos_y);
    virtual ~PowerUp();

    // Functions
    void applyEffect(Player* player);  // Increases the player's health
};

#endif // POWERUP_H
