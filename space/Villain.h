#ifndef VILLAIN_H
#define VILLAIN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"  // Assuming you already have a Bullet class

class Villain
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float movementDirection;  // Direction of movement (left or right)
    float leftBound;  // Left bound for movement
    float rightBound;
    float topBound; // Right bound for moveme
    float movementSpeed;
    float shootCooldown;
    float shootCooldownMax;
    int health;
    int maxHealth;

    std::vector<Bullet*> bullets;  // Villain's bullets

    void initVariables();
    void initTexture();
    void initSprite();

public:
    Villain(float pos_x, float pos_y);
    virtual ~Villain();

    // Accessors
    const sf::FloatRect getBounds() const;
    const bool canShoot() const;
    const int& getHealth() const;
    std::vector<Bullet*>& getBullets();

    // Modifiers
    void decreaseHealth(int amount);
    void shoot();
    void update();
    void render(sf::RenderTarget* target);
};

#endif // VILLAIN_H
