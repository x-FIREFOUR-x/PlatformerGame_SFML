#include "stdafx.h"
#include "Bullet.h"

void Bullet::initShape()
{
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setRadius(2.f);
}

Bullet::Bullet()
{
}

Bullet::Bullet(float dir_x, float x, float y, float movement_speed)
{
	this->direction.x = dir_x;
	this->movementSpeed = movement_speed;
	this->setPosition(x, y);
	this->initShape();
}

Bullet::~Bullet()
{

}

sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Bullet::setPosition(float pos_x, float pos_y)
{
	this->shape.setPosition(pos_x, pos_y);
}

void Bullet::update()
{
	this->shape.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
