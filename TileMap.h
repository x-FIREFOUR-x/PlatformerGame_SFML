#pragma once
#include "Tile.h"
class TileMap
{
private:
	std::vector<std::vector<Tile*>> tiles;

public:
	TileMap();
	~TileMap();

	void addTile(unsigned i, unsigned j, unsigned x, unsigned y);
	void removeTile(unsigned i, unsigned j);

	void update();
	void render(sf::RenderTarget& target);
};

