#pragma once
//#include "stdafx.h"
#include "Player.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	Player* player;

	void initWindow();
	void initPlayer();
public:
	Game();
	~Game();


	const sf::RenderWindow& getWindow()const;

	void updatePlayer();
	void update();

	void renderPlayer();
	void render();
};

