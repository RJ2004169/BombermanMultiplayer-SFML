#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "Client.h"
#include "DestructableWalls.h"
#include "IndestructableWalls.h"
#include "Bomb.h"

#pragma once


class Game
{
public:
	Game();
	void run();
	~Game();
private:
	void update();
	void procesEvents();
	void render();
	static const sf::Time timePerFrame;

	sf::RenderWindow mWindow;

	bool dir[4];

	sf::TcpSocket socket;

	unsigned short port;
	sf::IpAddress ipAdress;

	sf::Clock m_clock;

	std::vector<sf::Sprite> remotePlayers;

	Player pSprite;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::unique_ptr<Client> client;

	sf::Vector2f lastDirSent;
	bool movingDiagonal;

	sf::Time m_positionTimer;

	DestructableWalls dwSprite;
	IndestructableWalls iwSprite;
	Bomb bombSprite;
	Bomb enemyBombSprite;
	char name[10];

};