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
	void CollisionTopTile(Player* player, unsigned i, unsigned j);
	void CollisionBottomTile(Player* player, unsigned i, unsigned j);
	void CollisionSidesTile(Player* player, unsigned i, unsigned j);

	void update();

	void render(sf::RenderTarget& target);
};

