#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
{
	/*int column = 2;
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
	}*/

	tiles.push_back(std::vector<Tile*>());
	addTile(0, 0, 200, 500);
	addTile(0, 1, 300, 300);
	addTile(0, 2, 0, 400);
	addTile(0, 3, 400, 200);
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

void TileMap::moveTileMap(const float x)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			tiles[i][j]->move(x, 0);
			if (tiles[i][j]->GlobalBounds().left + tiles[i][j]->GlobalBounds().width <= 0)
				removeTile(i, j);
		}
	}
}

void TileMap::updateCollision(Player* player)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
				//collision bottom player with top tile  (player jump in tile)
			this->CollisionTopTile(player, i, j);

				//collision top player with bottom tile  (player jump head to tile)
			this->CollisionBottomTile(player, i, j);

				//Collision player with left tile and right tile
			this->CollisionSidesTile(player, i, j);
			
		}
	}
	
}

void TileMap::CollisionTopTile(Player* player, unsigned i, unsigned j)
{
	if (
		player->getPosition().y + player->getGlobalBounds().height > tiles[i][j]->GlobalBounds().top
		&& player->getPosition().y + player->getGlobalBounds().height < tiles[i][j]->GlobalBounds().top + tiles[i][j]->GlobalBounds().height
		&& player->getPosition().x + player->getGlobalBounds().width * 0.5 > tiles[i][j]->GlobalBounds().left
		&& player->getPosition().x + player->getGlobalBounds().width * 0.5 < tiles[i][j]->GlobalBounds().left + tiles[i][j]->GlobalBounds().width
	)
	{
		//std::cout << tiles[i][j]->GlobalBounds().top << " " << player->getGlobalBounds().top << " " << player->getGlobalBounds().height << "\n";
		player->resetVelosityY();
		player->setPosition(
			player->getPosition().x,
			tiles[i][j]->GlobalBounds().top - player->getGlobalBounds().height
		);
	}
}

void TileMap::CollisionBottomTile(Player* player, unsigned i, unsigned j)
{
	if (
		player->getPosition().y >= tiles[i][j]->GlobalBounds().top
		&& player->getPosition().y <= tiles[i][j]->GlobalBounds().top + tiles[i][j]->GlobalBounds().height
		&& player->getPosition().x + player->getGlobalBounds().width * 0.5 > tiles[i][j]->GlobalBounds().left
		&& player->getPosition().x + player->getGlobalBounds().width * 0.5 < tiles[i][j]->GlobalBounds().left + tiles[i][j]->GlobalBounds().width
	)
	{
		player->resetVelosityY();
		player->setPosition(
			player->getPosition().x,
			tiles[i][j]->GlobalBounds().top + tiles[i][j]->GlobalBounds().height
		);
	}
}

void TileMap::CollisionSidesTile(Player* player, unsigned i, unsigned j)
{
	if (
		player->getPosition().y + player->getGlobalBounds().height > tiles[i][j]->GlobalBounds().top
		&& player->getPosition().y < tiles[i][j]->GlobalBounds().top + tiles[i][j]->GlobalBounds().height
		&& player->getPosition().x + player->getGlobalBounds().width > tiles[i][j]->GlobalBounds().left
		&& player->getPosition().x < tiles[i][j]->GlobalBounds().left + tiles[i][j]->GlobalBounds().width
	)
	{
		float x;
		if (player->getPosition().x < tiles[i][j]->GlobalBounds().left + tiles[i][j]->GlobalBounds().width / 2)
			x = tiles[i][j]->GlobalBounds().left - player->getGlobalBounds().width;
		else
			x = tiles[i][j]->GlobalBounds().left + tiles[i][j]->GlobalBounds().width;
		player->setPosition(
			x,
			player->getPosition().y
		);
	}
}

bool TileMap::CollisionBullet(Bullet* bullet)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			if (this->tiles[i][j]->GlobalBounds().intersects(bullet->getBounds()))
			{
				return true;
			}
		}
	}

	return false;
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
