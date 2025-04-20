#include "PowerUps.h"
#include <iostream>

// Override the texture initialization to use a power-up texture
void PowerUp::initTexture()
{
    if (!this->texture.loadFromFile("Textures/health.png"))  // Replace with your texture path
    {
        std::cout << "ERROR::POWERUP::INITTEXTURE::Could not load texture file." << std::endl;
    }
}

// Constructor
PowerUp::PowerUp(float pos_x, float pos_y) : Enemy(pos_x, pos_y)
{
    this->initTexture();
    this->sprite.setTexture(this->texture);

    // Optionally, scale the power-up differently
    this->sprite.scale(3.5f, 3.5f);

    // Power-ups don't deal damage, so set damage to 0
    this->damage = 0;
}

// Destructor
PowerUp::~PowerUp()
{
}

// Function to apply the effect on the player
void PowerUp::applyEffect(Player* player)
{
    // Increase player's health
    player->setHp(player->getHp() + 10);  // Adjust health increase as needed

    // Cap health at max health
    if (player->getHp() > player->getHpMax())
    {
        player->setHp(player->getHpMax());
    }
}
