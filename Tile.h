#pragma once
class Tile
{
private:
	sf::RectangleShape shape;
	const bool damaging;

public:
	Tile(unsigned x, unsigned y, bool damaging = false);
	const sf::FloatRect GlobalBounds() const;

	void update();
	void render(sf::RenderTarget& target);
};

