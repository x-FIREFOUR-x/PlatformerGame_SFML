#include "stdafx.h"
#include "Tile.h"

Tile::Tile(unsigned x, unsigned y, bool damaging)
    :damaging(damaging)
{
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(200.f, 25.f));
    this->shape.setPosition(x, y);
}

const sf::FloatRect Tile::GlobalBounds() const
{
    return this->shape.getGlobalBounds();
}



void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
}
