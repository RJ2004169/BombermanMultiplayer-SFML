#include "Player.h"


Player::Player() : m_health(100), m_id(-1)
{
	if (!pTexture.loadFromFile("Media/player.png"))
		std::cout << "Error loading player.png" << std::endl;
	this->setTexture(pTexture);
	bombTimer = 0;
	spBombTimer = 0;
}


Player::~Player()
{
}

void Player::setRandomGameState()
{
	//Add in indestructable walls
	for (int i = 1; i < 10; i=i+2)
	{
		for (int j = 1; j < 10; j=j+2)
		{
			m_gameState[i][j] = 3;
		}
	}

	//Add destructable walls randomly
	srand(time(NULL));

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (m_gameState[i][j] != 3)
			{
				if ((rand() % 100 + 1) <= 50)
				{
					m_gameState[i][j] = 2;
				}
				else
				{
					m_gameState[i][j] = 0;
				}
			}
		}
	}
	while (true)
	{
		int i = rand() % 11, j = rand() % 11;
		if (m_gameState[i][j] == 0)
		{
			m_gameState[i][j] = 1;
			if (i > 0 && m_gameState[i - 1][j] != 3)
			{
				m_gameState[i - 1][j] = 0;
			}
			if (i < 10 && m_gameState[i+1][j] != 3)
			{
				m_gameState[i + 1][j] = 0;
			}
			if(j > 0 && m_gameState[i][j - 1] != 3)
			{
				m_gameState[i][j - 1] = 0;
			}
			if (j < 10 && m_gameState[i][j+1] != 3)
			{
				m_gameState[i][j + 1] = 0;
			}
			break;
		}
	}
}

void Player::moveRight()
{
	int found = 0;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (m_gameState[i][j] != 1)
				continue;
			else
			{
				found = 1;
				if (j < 10)
				{
					if (m_gameState[i][j + 1] != 2 && m_gameState[i][j + 1] != 3 && m_gameState[i][j + 1] != 4 && m_gameState[i][j + 1] != 6)
					{
						if (spBombTimer && spBombPosX == i && spBombPosY == j)
						{
							m_gameState[i][j] = 5;
							//spBombTimer++;
						}
						else if (bombTimer && bombPosX == i && bombPosY == j)
						{
							m_gameState[i][j] = 4;
							//bombTimer++;
						}
						else
						{
							m_gameState[i][j] = 0;
						}
						m_gameState[i][j + 1] = 1;

					}
				}
				break;
			}
		}
		if (found)
			break;
	}
}
void Player::moveLeft()
{
	int found = 0;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (m_gameState[i][j] != 1)
				continue;
			else
			{
				found = 1;
				if (j > 0)
				{
					if (m_gameState[i][j - 1] != 2 && m_gameState[i][j - 1] != 3 && m_gameState[i][j - 1] != 4 && m_gameState[i][j - 1] != 6)
					{
						if (spBombTimer && spBombPosX == i && spBombPosY == j)
						{
							m_gameState[i][j] = 5;
							//spBombTimer++;
						}
						else if (bombTimer && bombPosX == i && bombPosY == j)
						{
							m_gameState[i][j] = 4;
							//bombTimer++;
						}
						else
							m_gameState[i][j] = 0;
						m_gameState[i][j - 1] = 1;

					}
				}
				break;
			}
		}
		if (found)
			break;
	}
}
void Player::moveUp()
{
	int found = 0;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (m_gameState[i][j] != 1)
				continue;
			else
			{
				found = 1;
				if (i > 0)
				{
					if (m_gameState[i - 1][j] != 2 && m_gameState[i - 1][j] != 3 && m_gameState[i - 1][j] != 4 && m_gameState[i - 1][j] != 6)
					{
						if (spBombTimer && spBombPosX == i && spBombPosY == j)
						{
							m_gameState[i][j] = 5;
							//spBombTimer++;
						}
						else if (bombTimer && bombPosX == i && bombPosY == j)
						{
							m_gameState[i][j] = 4;
							//bombTimer++;
						}
						else
							m_gameState[i][j] = 0;
						m_gameState[i - 1][j] = 1;

					}
				}
				break;
			}
		}
		if (found)
			break;
	}
}
void Player::moveDown()
{
	int found = 0;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (m_gameState[i][j] != 1)
				continue;
			else
			{
				found = 1;
				if (i < 10)
				{
					if (m_gameState[i + 1][j] != 2 && m_gameState[i + 1][j] != 3 && m_gameState[i + 1][j] != 4 && m_gameState[i + 1][j] != 6)
					{
						if (spBombTimer && spBombPosX == i && spBombPosY == j)
						{
							m_gameState[i][j] = 5;
							//spBombTimer++;
						}
						else if (bombTimer && bombPosX == i && bombPosY == j)
						{
							m_gameState[i][j] = 4;
							//bombTimer++;
						}
						else
							m_gameState[i][j] = 0;
						m_gameState[i + 1][j] = 1;

					}
				}
				break;
			}
		}
		if (found)
			break;
	}
}

bool Player::placeBomb()
{
	if (bombTimer == 0)
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				if (m_gameState[i][j] == 1)
				{
					bombPosX = i; bombPosY = j;
					bombTimer++;
					break;
				}
			}
		}
	}
	return true;
}
bool Player::placeSpBomb()
{
	if (spBombTimer == 0)
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				if (m_gameState[i][j] == 1)
				{
					spBombPosX = i; spBombPosY = j;
					spBombTimer++;
					break;
				}
			}
			if (spBombTimer)
				break;
		}
	}
	return true;
}
bool Player::placeEnemyBomb(int i, int j)
{
	m_gameState[i][j] = 6;
	incrementEnemyBombTimer();
	return true;
}

int Player::getEnemyBombTimer()
{
	return enemyBombTimer;
}
int Player::getBombTimer()
{
	return bombTimer;
}
int Player::getSpBombTimer()
{
	return spBombTimer;
}

void Player::incrementBombTimer()
{

	if (bombTimer > 50)
	{
		bombTimer = 0;
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				if (m_gameState[i][j] == 4)
				{
					if (i > 0 && m_gameState[i - 1][j] != 3)
					{
						m_gameState[i - 1][j] = 0;
					}
					if (i < 10 && m_gameState[i + 1][j] != 3)
					{
						m_gameState[i + 1][j] = 0;
					}
					if (j > 0 && m_gameState[i][j - 1] != 3)
					{
						m_gameState[i][j - 1] = 0;
					}
					if (j < 10 && m_gameState[i][j + 1] != 3)
					{
						m_gameState[i][j + 1] = 0;
					}
					m_gameState[i][j] = 0;
				}
			}
		}
	}
	else
	{
		bombTimer++;
	}
}
void Player::incrementEnemyBombTimer()
{

	if (enemyBombTimer > 50)
	{
		enemyBombTimer = 0;
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				if (m_gameState[i][j] == 6)
				{
					if (i > 0 && m_gameState[i - 1][j] != 3)
					{
						m_gameState[i - 1][j] = 0;
					}
					if (i < 10 && m_gameState[i + 1][j] != 3)
					{
						m_gameState[i + 1][j] = 0;
					}
					if (j > 0 && m_gameState[i][j - 1] != 3)
					{
						m_gameState[i][j - 1] = 0;
					}
					if (j < 10 && m_gameState[i][j + 1] != 3)
					{
						m_gameState[i][j + 1] = 0;
					}
					m_gameState[i][j] = 0;
				}
			}
		}
	}
	else
	{
		enemyBombTimer++;
	}
}

void Player::incrementSpBombTimer()
{
	if (spBombTimer > 100)
	{
		spBombTimer = 0;
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				if (m_gameState[i][j] == 5)
				{
					m_gameState[i][j] = 0;
				}
			}
		}
	}
	else
		spBombTimer++;
}

int Player::getSpBombPosX()
{
	return spBombPosX;
}

int Player::getSpBombPosY()
{
	return spBombPosY;
}
