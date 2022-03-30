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

	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->attackCooldown >= this->attackCooldownMax)
	{
		if (player->getAnimState() == PLAYER_ANIMATION_STATE::MOVING_RIGHT || player->getAnimState() == PLAYER_ANIMATION_STATE::MOVING_LEFT || player->getAnimState() == PLAYER_ANIMATION_STATE::IDLE)
		{
			this->attackCooldown = 0;
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
	this->attackCooldown++;
}


void Game::updatePlayer()
{
	this->player->update();
}

void Game::updateCollision()
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

	tileMap.updateCollision(player);
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


	for (int i = 0; i < bullets.size(); i++)
	{
		this->bullets[i]->update();
	}

	this->updateCollision();
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
