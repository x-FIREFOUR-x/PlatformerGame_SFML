#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
{
	int column = 2;
	int line = 3;
	float distance_Y = 250;			//distance between line tiles
	float distance_X = 300;			//distance between column tiles
	float start_pos = 150;			//start locate tiles in column
	for (int i = 0; i < column; i++)
	{ 
		tiles.push_back(std::vector<Tile*>());
		for (int j = 0; j < line; j++)
		{
			if (i % 2 == 0)
				this->addTile(i, j, distance_X * i, distance_Y * j);
			else
				this->addTile(i, j, distance_X * i, distance_Y * j + start_pos);
		}
	}
}

TileMap::~TileMap()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			delete tiles[i][j];
		}
	}
}

void TileMap::addTile(unsigned i, unsigned j, unsigned x, unsigned y)
{
	Tile* tile = new Tile(x, y);
	tiles[i].insert(tiles[i].begin() + j, tile);
}

void TileMap::removeTile(unsigned i, unsigned j)
{
	delete tiles[i][j];
	tiles[i].erase(tiles[i].begin() + j);
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int j = 0; j < this->tiles[i].size(); j++)
		{
			this->tiles[i][j]->render(target);
		}
	}
}
