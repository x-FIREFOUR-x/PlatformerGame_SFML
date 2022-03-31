#pragma once
#include "Bullet.h"

enum PLAYER_ANIMATION_STATE
{
	IDLE = 0,
	MOVING_LEFT,
	MOVING_RIGHT,
	JUMPING,
	FALING,
	FALING_LEFT,
	FALING_RIGHT
};

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;

	
	//Animations
	sf::Clock animationTimer;
	short animState;
	sf::IntRect currentFrame;
	bool animationSwitch;

	//Physics
	sf::Vector2f speed;
				//parameters running
	float speedMax;
	float speedMin;
	float acceleration;
	float drag;
				//parameters falling and jumping
	float gravity;
	float speedMaxFall;
	float speedJump;
				//parameters falling right or left
	float speedFallX;
	float accelerationFallX;
	float speedFallXMax;
	float speedFallXMin;

	//Atack
	float attackCooldown;
	float attackCooldownMax;



	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void initPhysics();

public:
	Player();
	virtual ~Player();

		//Accessors
	const bool& getAnimSwitch();
	const sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f getPosition() const;
	const short getAnimState() const;
	const sf::Vector2f getSpriteOrigin() const;
	const bool canAttack();

		//Modifiers
	void setPosition(const float x, const float y);
	void resetVelosityY();
	

		//Functions
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void moveFalling(const float dir_x);
	void defState();
	void animFire();

	void updatePhysics();
	void updateAnimations();
	void updateMovement();
	void updateAttack();
	void update();

	void render(sf::RenderTarget& target);
};

