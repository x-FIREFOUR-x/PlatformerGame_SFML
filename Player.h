#pragma once
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;


	//Animations
	sf::IntRect currentFrame;

	void initTexture();
	void initSprite();

public:
	Player();
	virtual ~Player();

	void updateMovement();
	void update();

	void render(sf::RenderTarget& target);
};

