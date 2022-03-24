 #include "stdafx.h"
#include "Player.h"

void Player::initVariables()
{
	this->animState = PLAYER_ANIMATION_STATE::IDLE;
}

void Player::initTexture()
{
	if (!this->textureSheet.loadFromFile("Texture/playerSheet.png"))
		std::cout << "ERROR::PLAYER::Could not load texture 'Texture/playerSheet.png'";
}

void Player::initSprite()
{
	this->sprite.setTexture(textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 32, 50);
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

void Player::updatePhysics()
{

}

void Player::updateAnimations()
{

	if (this->animState == PLAYER_ANIMATION_STATE::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f)
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 160.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATE::MOVING_RIGHT)
	{

		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f)
		{
			this->currentFrame.top = 50.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 360.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else
		this->animationTimer.restart();
	
	
}

void Player::updateMovement()
{
	this->animState = PLAYER_ANIMATION_STATE::IDLE;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		this->sprite.move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATE::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		this->sprite.move(1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATE::MOVING_RIGHT;
	}

	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		this->sprite.move(0.f, -1.f);
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		this->sprite.move(0.f, 1.f);
		
	}*/
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
