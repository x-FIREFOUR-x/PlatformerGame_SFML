 #include "stdafx.h"
#include "Player.h"

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Texture/playerSheet.png"))
		std::cout << "ERROR::PLAYER::Could not load texture 'Texture/playerSheet.png'";
}

void Player::initSprite()
{
	this->sprite.setTexture(textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 32, 58);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.scale(3.f, 3.f);
}

Player::Player()
{
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

void Player::updateMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		this->sprite.move(-1.f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		this->sprite.move(1.f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		this->sprite.move(0.f, -1.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		this->sprite.move(0.f, 1.f);
	}
}

void Player::update()
{
	this->updateMovement();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
