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

void Player::initPhysics()
{
	this->velocityMax = 10.f;
	this->velocityMin = 1.f;
	this->acceleration = 2.f;
	this->drag = 0.93f;
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();
}

Player::~Player()
{
}

void Player::move(const float dir_x, const float dir_y)
{
		//increase speed
	this->velocity.x += dir_x * this->acceleration;
	//this->velocity.y += dir_y * this->acceleration;

		//limit max velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);
}

void Player::updatePhysics()
{
		//dicrease speed
	this->velocity *= this->drag;

		//limit min velocity
	if (std::abs(this->velocity.x) < this->velocityMin)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->velocityMin)
		this->velocity.y = 0.f;

		//move
	this->sprite.move(this->velocity);
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
		this->move(-1.f, 0.f);
		this->animState = PLAYER_ANIMATION_STATE::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		this->move(1.f, 0.f);
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
	this->updatePhysics();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
