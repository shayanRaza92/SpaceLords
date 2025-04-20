#include "Villain.h"
#include <iostream>

void Villain::initVariables()
{
    this->movementSpeed = 1.f;  // Movement speed (optional, for basic movement)
    this->shootCooldownMax = 50.f;  // Cooldown for shooting bullets
    this->shootCooldown = this->shootCooldownMax;
    this->health = 30;  // Initial health
    this->maxHealth = 30;
}

void Villain::initTexture()
{
    // Load texture for the villain
    if (!this->texture.loadFromFile("Textures/2.png"))
    {
        std::cout << "ERROR::VILLAIN::INITTEXTURE::Could not load texture file." << std::endl;
    }
}

void Villain::initSprite() 
{
    // Set the texture and sprite
    this->sprite.setTexture(this->texture);

    //Resize the sprite
	this->sprite.scale(0.4f, 0.4f);

    
}


Villain::Villain(float pos_x, float pos_y)
{
    this->initVariables();
    this->initTexture();
    this->initSprite();
    this->sprite.setPosition(200, 100);
    this->leftBound = 100.f;  // Starting left position
    this->rightBound = 700.f;  // Starting right position
    this->movementDirection = 1.f;  // Start by moving right
}

Villain::~Villain()
{
    for (auto* bullet : this->bullets)
    {
        delete bullet;  // Clean up bullets
    }
}

const sf::FloatRect Villain::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

const bool Villain::canShoot() const
{
    return this->shootCooldown <= 0.f;
}

const int& Villain::getHealth() const
{
    return this->health;
}

std::vector<Bullet*>& Villain::getBullets()
{
    return this->bullets;
}

void Villain::decreaseHealth(int amount)
{
    this->health -= amount;
    if (this->health <= 0)
    {
        this->health = 0;
        std::cout << "Villain defeated!" << std::endl;
    }
}

void Villain::shoot()
{
    if (this->canShoot())
    {
        sf::Texture* bulletTexture = new sf::Texture();
        if (!bulletTexture->loadFromFile("Textures/bullet_enemy.png"))
        {
            std::cout << "ERROR::VILLAIN::SHOOT::Could not load bullet texture." << std::endl;
            delete bulletTexture;  // Avoid memory leak if texture fails
            return;
        }

        // Create a new bullet and add it to the vector
        this->bullets.push_back(new Bullet(
            bulletTexture,
            this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2.f, 
            this->sprite.getPosition().y + this->sprite.getGlobalBounds().height,
            0.f, 1.f, 5.f  // Shoot downward
        ));

        // Reset cooldown after shooting
        this->shootCooldown = this->shootCooldownMax;
    }
}

void Villain::update()
{
    // Decrease shoot cooldown if necessary
    if (this->shootCooldown > 0.f)
        this->shootCooldown -= 1.f;

    // Move the villain left or right based on its direction
    this->sprite.move(this->movementDirection * this->movementSpeed, 0.f);  // Only horizontal movement

    // Check if the villain hits the left or right bounds
    if (this->sprite.getPosition().x <= this->leftBound)  // If it hits the left boundary
    {
        this->movementDirection = 1.f;  // Change direction to right
    }
    else if (this->sprite.getPosition().x >= this->rightBound)  // If it hits the right boundary
    {
        this->movementDirection = -1.f;  // Change direction to left
    }

    // Shoot if the cooldown is finished
    if (this->canShoot())
    {
        this->shoot();  // Call shoot to create a bullet
    }

    // Update bullets
    for (auto* bullet : this->bullets)
    {
        bullet->update();
    }

    // Remove bullets that are out of screen
    this->bullets.erase(
        std::remove_if(this->bullets.begin(), this->bullets.end(),
            [](Bullet* bullet) {
                if (bullet->getBounds().top > 600.f)  // Screen height
                {
                    delete bullet;
                    return true;
                }
                return false;
            }),
        this->bullets.end());
}

void Villain::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);  // Render the villain sprite

    // Render bullets
    for (auto* bullet : this->bullets)
    {
        bullet->render(target);  // Render each bullet
    }
}
