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
	this->speedMax = 20.f;
	this->speedMin = 2.f;

	this->acceleration = 3.2f;
	this->drag = 0.90f;

	this->gravity = 4.f;

	this->speedMaxFall = 15.f;
	this->speedJump = -50.f;

	this->accelerationFallX = 1.f;
	this->speedFallXMin = 1.f;
	this->speedFallXMax = 10.f;
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
	this->speed.y = 0.f;
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
		//increase speed
	this->speed.x += dir_x * this->acceleration;
	
		//limit max speed
	if (std::abs(this->speed.x) > this->speedMax)
		this->speed.x = this->speedMax * ((this->speed.x < 0.f) ? -1.f : 1.f);

	this->speed.y = dir_y * this->speedJump;

}

void Player::moveFalling(const float dir_x)
{
	//increase speed
	this->speed.x += dir_x * this->accelerationFallX;

	//limit max speed
	if (std::abs(this->speed.x) > this->speedMaxFall)
		this->speed.x = this->speedMaxFall * ((this->speed.x < 0.f) ? -1.f : 1.f);

}

void Player::defState()
{
	if (speed.y > 0 && speed.x == 0)
		this->animState = PLAYER_ANIMATION_STATE::FALING;
	else if (speed.y > 0 && speed.x > 0)
		this->animState = PLAYER_ANIMATION_STATE::FALING_RIGHT;
	else if (speed.y > 0 && speed.x < 0)
		this->animState = PLAYER_ANIMATION_STATE::FALING_LEFT;
	else if (speed.y < 0)
		this->animState = PLAYER_ANIMATION_STATE::JUMPING;
	else if (speed.x > 0 && animState != PLAYER_ANIMATION_STATE::JUMPING)
		this->animState = PLAYER_ANIMATION_STATE::MOVING_RIGHT;
	else if (speed.x < 0 && animState != PLAYER_ANIMATION_STATE::JUMPING)
		this->animState = PLAYER_ANIMATION_STATE::MOVING_LEFT;
	else if (speed.x == 0 && speed.y == 0 && animState != PLAYER_ANIMATION_STATE::JUMPING)
		this->animState = PLAYER_ANIMATION_STATE::IDLE;

}


void Player::updatePhysics()
{
	//Gravity
	this->speed.y += 1.0 * this->gravity;
	/*if (std::abs(this->speed.y) > this->speedMaxFall)
		this->speed.y = this->speedMaxFall * ((this->speed.y < 0.f) ? -1.f : 1.f);*/
	if (this->speed.y > this->speedMaxFall)
		this->speed.y = this->speedMaxFall;
	

		//dicrease speed
	this->speed *= this->drag;

		//limit min speed
	if (std::abs(this->speed.x) < this->speedMin)
		this->speed.x = 0.f;
	if (std::abs(this->speed.y) < this->speedMin)
		this->speed.y = 0.f;

		//move
	this->sprite.move(this->speed);
}

void Player::updateAnimations()
{
	

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

		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 200.f;
			this->currentFrame.left += 40.f;
			if (this->currentFrame.left >= 40.f)
				this->currentFrame.left = 40.f;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATE::FALING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 200.f;
			this->currentFrame.left = 40.f;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-3.f, 3.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 3.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATE::FALING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimSwitch())
		{
			this->currentFrame.top = 200.f;
			this->currentFrame.left = 40.f;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(3.f, 3.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else
		this->animationTimer.restart();
	
	
}

void Player::updateMovement()
{
	this->defState();

	if ((animState == PLAYER_ANIMATION_STATE::IDLE) || (animState == PLAYER_ANIMATION_STATE::MOVING_LEFT) || (animState == PLAYER_ANIMATION_STATE::MOVING_RIGHT))
	{
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			this->move(0, 1.f);
			this->animState = PLAYER_ANIMATION_STATE::JUMPING;
		}
	}
	else if (animState != PLAYER_ANIMATION_STATE::JUMPING)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			this->moveFalling(-1.f);
			this->animState = PLAYER_ANIMATION_STATE::FALING_LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			this->moveFalling(1.f);
			this->animState = PLAYER_ANIMATION_STATE::FALING_RIGHT;
		}
	}
	

}

void Player::updateFire()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

	}
}

void Player::update()
{
	this->updateMovement();
	this->updateFire();
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

	sf::CircleShape circ2;
	circ2.setFillColor(sf::Color::Red);
	circ2.setRadius(2.f);
	circ2.setPosition(sf::Vector2f(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width, this->sprite.getPosition().y));
	target.draw(circ2);

	sf::CircleShape circ3;
	circ3.setFillColor(sf::Color::Red);
	circ3.setRadius(2.f);
	circ3.setPosition(sf::Vector2f(this->sprite.getPosition().x + this->sprite.getGlobalBounds().width, this->sprite.getPosition().y + this->sprite.getGlobalBounds().height));
	target.draw(circ3);

	sf::CircleShape circ4;
	circ4.setFillColor(sf::Color::Red);
	circ4.setRadius(2.f);
	circ4.setPosition(sf::Vector2f(this->sprite.getPosition().x , this->sprite.getPosition().y + this->sprite.getGlobalBounds().height));
	target.draw(circ4);
}
