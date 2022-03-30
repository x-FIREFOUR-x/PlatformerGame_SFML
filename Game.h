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

	//Attack
	std::vector<Bullet*> bullets;
	float attackCooldown;
	float attackCooldownMax;

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
	void update();

	void renderPlayer();
	void render();
};

