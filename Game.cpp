#include "stdafx.h"
#include "Game.h"


void Game::initWindow()
{
	//this->window.create(sf::VideoMode::getDesktopMode(), )
	this->window.create(sf::VideoMode(800, 600), "Platformer", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
}

void Game::initPlayer()
{
	this->player = new Player();

}

void Game::initTileMap()
{
}

Game::Game()
{
	this->initWindow();
	this->initPlayer();
	this->initTileMap();
}

Game::~Game()
{
	delete this->player;

}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}



void Game::pressFire()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->player->animFire();
		Bullet* bullet;
		if (player->getSpriteOrigin().x == 0)
		{
			bullet = new Bullet(
				1,
				player->getGlobalBounds().left + player->getGlobalBounds().width,
				player->getGlobalBounds().top + player->getGlobalBounds().height / 2,
				25
			);
			bullets.push_back(bullet);
		}
		else
		{
			bullet = new Bullet(
				-1,
				player->getGlobalBounds().left,
				player->getGlobalBounds().top + player->getGlobalBounds().height / 2,
				25
			);
			bullets.push_back(bullet);
		}

	}
}


void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateCollisionWindow()
{
		//Collision bottom of screen;
	if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
	{
		this->player->resetVelosityY();
		this->player->setPosition(
			this->player->getPosition().x,
			this->window.getSize().y - this->player->getGlobalBounds().height
		);
	}

		////Collision top of screen
	if (this->player->getPosition().y < 0)
	{
		this->player->resetVelosityY();
		this->player->setPosition(this->player->getPosition().x, 0);
	}

		//Collision left side of screen
	if (this->player->getPosition().x < 0)
	{
		this->player->setPosition(0, this->player->getPosition().y);
	}

}

void Game::updateCollisionTileMap()
{
	tileMap.updateCollision(player);
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (int i = 0; i < bullets.size(); i++)
	{
		this->bullets[i]->update();

				//Collision border window
		if (bullets[i]->getBounds().left >  window.getSize().x || bullets[i]->getBounds().left  + bullets[i]->getBounds().width < 0)
		{
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
				//Collision Tile
		else
		{
			bool CollisionTile = this->tileMap.CollisionBullet(bullets[i]);
			if (CollisionTile)
			{
				delete this->bullets.at(counter);
				this->bullets.erase(this->bullets.begin() + counter);
				--counter;
			}
		}
				
		++counter;
	}
}

void Game::updateMapWorld()
{
	float limit = this->window.getSize().x * 0.6;
	if (this->player->getPosition().x > limit)
	{
		float x = this->player->getPosition().x - limit;
		this->tileMap.moveTileMap(-x/2);
		this->player->setPosition(
			this->window.getSize().x * 0.6,
			this->player->getPosition().y
		);
	}

}



void Game::update()
{
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			this->window.close();

		if (
			this->ev.type == sf::Event::KeyReleased &&
			(
					this->ev.key.code == sf::Keyboard::A ||
					this->ev.key.code == sf::Keyboard::D ||
					this->ev.key.code == sf::Keyboard::W ||
					this->ev.key.code == sf::Keyboard::S ||
					this->ev.key.code == sf::Keyboard::Space
				)
			)
		{
			this->player->resetAnimationTimer();
		}
			
	}
	this->updatePlayer();

	this->pressFire();
	this->updateBullets();

	this->updateCollisionWindow();
	this->updateCollisionTileMap();

	this->updateMapWorld();
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::render()
{
	this->window.clear();

	this->tileMap.render(this->window);

	this->renderPlayer();

	for (int i = 0; i < bullets.size(); i++)
	{
		this->bullets[i]->render(this->window);
	}


	this->window.display();
}
