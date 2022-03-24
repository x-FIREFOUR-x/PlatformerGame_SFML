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

	//Physics
	sf::Vector2f velocity;
	float acceleration;
	float deceleration;


	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();

public:
	Player();
	virtual ~Player();

	void updatePhysics();
	void updateAnimations();
	void updateMovement();
	void update();

	void render(sf::RenderTarget& target);
};

