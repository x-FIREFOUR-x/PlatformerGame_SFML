#pragma once
//#include "stdafx.h"
#include "Player.h"
#include "TileMap.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	TileMap tileMap;

	Player* player;

	void initWindow();
	void initPlayer();
	void initTileMap();
public:
	Game();
	~Game();


	const sf::RenderWindow& getWindow()const;

	void updatePlayer();
	void updateCollision();
	void update();

	void renderPlayer();
	void render();
};

