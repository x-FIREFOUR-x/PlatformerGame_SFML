#pragma once
#include "Tile.h"
#include "Player.h"
class TileMap
{
private:
	std::vector<std::vector<Tile*>> tiles;

public:
	TileMap();
	~TileMap();

	void addTile(unsigned i, unsigned j, unsigned x, unsigned y);
	void removeTile(unsigned i, unsigned j);

	void updateCollision(Player* player);

	void update();
	void render(sf::RenderTarget& target);
};

