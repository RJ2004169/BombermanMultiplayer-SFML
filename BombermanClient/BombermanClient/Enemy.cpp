#include "Enemy.h"


Enemy::Enemy(int id, sf::Vector2f position, std::string name) : m_health(100), m_id(id), m_name("default")
{
	if (!pTexture.loadFromFile("Media/enemy.jpg"))
		std::cout << "Error loading enemy.jpg" << std::endl;
	this->setTexture(pTexture);
	//this->setPosition(position);
	this->setName(name);
}


Enemy::~Enemy()
{
}
