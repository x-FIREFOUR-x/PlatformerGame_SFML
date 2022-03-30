#ifndef BULLET_H
#define BULLET_H

#include<SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
private:
	sf::CircleShape shape;

	sf::Vector2f direction;
	float movementSpeed;

	void initShape();

public:
	Bullet();
	Bullet(float dir_x, float x, float y, float movement_speed);
	virtual ~Bullet();


	//Accessor
	sf::FloatRect getBounds()const;

	//Modify
	void setPosition(float pos_x, float pos_y);

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif


