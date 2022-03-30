#pragma once
//#include "stdafx.h"
#include "Player.h"
#include "TileMap.h"
#include "Bullet.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	TileMap tileMap;

	Player* player;

	std::vector<Bullet*> bullets;
	
	void initWindow();
	void initPlayer();
	void initTileMap();
public:
	Game();
	~Game();


	const sf::RenderWindow& getWindow()const;

	void pressFire();
	void updatePlayer();
	void updateCollision();
	void updateBullets();
	void update();

	void renderPlayer();
	void render();
};

