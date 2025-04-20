#include "Enemy.h"
#include <iostream>

void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3; //min = 3 max = 10
	this->type		= 0;
	this->speed		= static_cast<float>(this->pointCount/3);
	this->hpMax		= static_cast<int>(this->pointCount);
	this->hp		= this->hpMax;
	this->damage	= this->pointCount;
	this->points	= this->pointCount;
}

void Enemy::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile("Textures/asteroid.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Enemy::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//Resize the sprite
	this->sprite.scale(0.3f, 0.3f);
}
Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	
	this->sprite.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

//Accessors
const sf::FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int & Enemy::getPoints() const
{
	return this->points;
}

const int & Enemy::getDamage() const
{
	return this->damage;
}

//Functions
void Enemy::update()
{
	this->sprite.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget * target)
{
	target->draw(this->sprite);
}