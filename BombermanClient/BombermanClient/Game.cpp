#include "Game.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
{
	m_positionTimer = sf::Time::Zero;
	port = 45000;
	//ipAdress = "172.18.24.67";
	std::cout << "Enter the IP adress from Server: ";
	std::cin >> ipAdress;
	std::cout << "Enter Name: ";
	std::cin >> name;
	client = std::make_unique<Client>(ipAdress, port);

	pSprite.setName(name);
	pSprite.setRandomGameState();

	mWindow.create(sf::VideoMode(1100, 1100), "Bomberman");
	socket.setBlocking(false);
	mWindow.setFramerateLimit(60);

	dir[0] = 0;
	dir[1] = 0;
	dir[2] = 0;
	dir[3] = 0;

	srand(time(0));
	sf::Texture enemyBombTexture;
	enemyBombTexture.loadFromFile("Media/spBomb.jpg");
	enemyBombSprite.setTexture(enemyBombTexture);
}

Game::~Game()
{
	client->disconnect(&pSprite);
}
void Game::run()
{
	//TODO fix timestep
	while (mWindow.isOpen())
	{
		procesEvents();
		update();
		render();
	}
}


void Game::procesEvents()
{
	//TODO organize events
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			mWindow.close();
			break;
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				mWindow.close();
				break;
			case sf::Keyboard::W:
				pSprite.moveLeft();
				break;
			case sf::Keyboard::A:
				pSprite.moveUp();
				break;
			case sf::Keyboard::S:
				pSprite.moveRight();
				break;
			case sf::Keyboard::D:
				pSprite.moveDown();
				break;
			case sf::Keyboard::Space:
				pSprite.placeBomb();
				break;
			case sf::Keyboard::P:
				pSprite.placeSpBomb();
				break;
			}
			break;

		}
	}
}


void Game::update()
{
	if (pSprite.getBombTimer())
	{
		pSprite.incrementBombTimer();
	}
	if (pSprite.getEnemyBombTimer())
	{
		pSprite.incrementEnemyBombTimer();
	}
	if (pSprite.getSpBombTimer())
	{
		client->sendSpBomb(&pSprite);
		pSprite.incrementSpBombTimer();
	}
	//Send direction
	if (lastDirSent != pSprite.getDirection())
	{
		client->send(&pSprite); // send move data
		lastDirSent = pSprite.getDirection();
	}
	//Send position 1 time every 1 second
	m_positionTimer += m_clock.restart();
	if (m_positionTimer >= sf::seconds(0.5))
	{
		client->sendPosition(&pSprite);
		m_positionTimer = sf::Time::Zero;
	}

	//Recive data from network
	client->receive(enemies, &pSprite);


	/*for (unsigned int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->move(enemies[i]->getDirection());
	}*/

}


void Game::render()
{
	mWindow.clear(sf::Color::White);

	int playerDead = 1;
	for (int j = 0; j < 11; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			if (pSprite.m_gameState[i][j] == 1)
			{
				pSprite.setPosition(i * 100, j * 100);
				mWindow.draw(pSprite);
				playerDead = 0;
			}
			if (pSprite.m_gameState[i][j] == 2)
			{
				//dwSprite.setScale(0.28f, 0.28f);
				dwSprite.setPosition(i * 100, j * 100);
				mWindow.draw(dwSprite);
			}
			if (pSprite.m_gameState[i][j] == 3)
			{
				iwSprite.setPosition(i * 100, j * 100);
				mWindow.draw(iwSprite);
			}
			if (pSprite.m_gameState[i][j] == 4)
			{
				bombSprite.setPosition(i * 100, j * 100);
				mWindow.draw(bombSprite);
			}
			if (pSprite.m_gameState[i][j] == 5)
			{
				bombSprite.setPosition(i * 100, j * 100);
				mWindow.draw(bombSprite);
			}
			if (pSprite.m_gameState[i][j] == 6)
			{
				enemyBombSprite.setPosition(i * 100, j * 100);
				mWindow.draw(enemyBombSprite);
			}
		}
	}
	if (playerDead)
	{
		client->disconnect(&pSprite);
		mWindow.close();
	}

	for (unsigned int i = 0; i < enemies.size(); i++)
		mWindow.draw(*enemies[i]);
	
	mWindow.display();
}