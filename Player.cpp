 #include "stdafx.h"
#include "Player.h"

void Player::initTexture()
{
	//this->textureSheet.loadFromFile("Textures/");
}

void Player::initSprite()
{
	//this->sprite.
}

Player::Player()
{
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

void Player::update()
{
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
