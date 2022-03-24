#pragma once
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;

	sf::Clock animationTimer;
	bool moving;

	//Animations
	sf::IntRect currentFrame;

	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();

public:
	Player();
	virtual ~Player();

	void updateAnimations();
	void updateMovement();
	void update();

	void render(sf::RenderTarget& target);
};

