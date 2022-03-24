 #include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->moving = false;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Texture/playerSheet.png"))
		std::cout << "ERROR::PLAYER::Could not load texture 'Texture/playerSheet.png'";
}

void Player::initSprite()
{
	this->sprite.setTexture(textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 32, 52);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.scale(2.5f, 2.5f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
}

Player::~Player()
{
}

void Player::updateAnimations()
{
	if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f) 
	{
		if (this->moving == false)
		{
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 160.f)
				this->currentFrame.left = 0;
		}

		this->animationTimer.restart();
		this->sprite.setTextureRect(this->currentFrame);
	}
	
}

void Player::updateMovement()
{
	this->moving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		this->sprite.move(-1.f, 0.f);
		this->moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		this->sprite.move(1.f, 0.f);
		this->moving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		this->sprite.move(0.f, -1.f);
		this->moving = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		this->sprite.move(0.f, 1.f);
		this->moving = true;
	}
}

void Player::update()
{
	this->updateMovement();
	this->updateAnimations();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
