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
	this->sprite.scale(3.f, 3.f);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::initPhysics()
{
	this->velocityMax = 20.f;
	this->velocityMin = 2.f;
	this->acceleration = 3.2f;
	this->drag = 0.87f;
	this->gravity = 4.f;
	this->velocityMaxFall = 15.f;
	this->velocityJump = -50.f;
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

const bool& Player::getAnimSwitch()
{
	bool anim_swith = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_swith;
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds(); 
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVelosityY()
{
	this->velocity.y = 0.f;
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
		//increase speed
	this->velocity.x += dir_x * this->acceleration;
	
		//limit max velocity
	if (std::abs(this->velocity.x) > this->velocityMax)
		this->velocity.x = this->velocityMax * ((this->velocity.x < 0.f) ? -1.f : 1.f);

	this->velocity.y = dir_y * this->velocityJump;

}

void Player::defState()
{
	if (velocity.y > 0)
		this->animState = PLAYER_ANIMATION_STATE::FALING;
	else if (velocity.y < 0)
		this->animState = PLAYER_ANIMATION_STATE::JUMPING;
	else if (velocity.x > 0)
		this->animState = PLAYER_ANIMATION_STATE::MOVING_RIGHT;
	else if (velocity.x < 0)
		this->animState = PLAYER_ANIMATION_STATE::MOVING_LEFT;
	else if (velocity.x == 0 && velocity.y == 0 && animState != PLAYER_ANIMATION_STATE::JUMPING)
		this->animState = PLAYER_ANIMATION_STATE::IDLE;

}


void Player::updatePhysics()
{
	//Gravity
	this->velocity.y += 1.0 * this->gravity;
	/*if (std::abs(this->velocity.y) > this->velocityMaxFall)
		this->velocity.y = this->velocityMaxFall * ((this->velocity.y < 0.f) ? -1.f : 1.f);*/
	if (this->velocity.y > this->velocityMaxFall)
		this->velocity.y = this->velocityMaxFall;
	

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
	this->defState();

	if (this->animState == PLAYER_ANIMATION_STATE::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
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

		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 50.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 360.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(3.f, 3.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATE::MOVING_LEFT)
	{

		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch() )
		{
			this->currentFrame.top = 50.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 360.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			
		}
		this->sprite.setScale(-3.f, 3.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 3.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATE::JUMPING)
	{
		
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 150.f;
			this->currentFrame.left = 0;
			/*this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 40.f)
				this->currentFrame.left = 40.f;*/

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATE::FALING)
	{

		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || this->getAnimSwitch())
		{
			this->currentFrame.top = 200.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 40.f)
				this->currentFrame.left = 40.f;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}
	}
	else
		this->animationTimer.restart();
	
	
}

void Player::updateMovement()
{
	//std::cout << animState <<std:: endl;
	//this->animState = PLAYER_ANIMATION_STATE::IDLE;

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && (animState != PLAYER_ANIMATION_STATE::JUMPING) && (animState != PLAYER_ANIMATION_STATE::FALING))
	{
		this->move(0, 1.f);
		this->animState = PLAYER_ANIMATION_STATE::JUMPING;
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

	sf::CircleShape circ;
	circ.setFillColor(sf::Color::Red);
	circ.setRadius(2.f);
	circ.setPosition(this->sprite.getPosition());

	target.draw(circ);
}
