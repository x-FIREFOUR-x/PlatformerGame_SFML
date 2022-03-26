#pragma once

enum PLAYER_ANIMATION_STATE
{
	IDLE = 0,
	MOVING_LEFT,
	MOVING_RIGHT,
	JUMPING,
	FALING
};

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;

	sf::Clock animationTimer;

	//Animations
	short animState;
	sf::IntRect currentFrame;
	bool animationSwitch;

	//Physics
	sf::Vector2f velocity;
	float velocityMax;
	float velocityMin;
	float acceleration;
	float drag;
	float gravity;
	float velocityMaxFall;

	float velocityJump;



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


		//Modifiers
	void setPosition(const float x, const float y);
	void resetVelosityY();

		//Functions
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void defState();
	
	void updatePhysics();
	void updateAnimations();
	void updateMovement();
	void update();

	void render(sf::RenderTarget& target);
};

