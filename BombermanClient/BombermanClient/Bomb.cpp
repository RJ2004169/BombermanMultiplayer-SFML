#include "Bomb.h"
#include <iostream>

Bomb::Bomb()
{
	if (!bTexture.loadFromFile("Media/bomb.jpg"))
		std::cout << "Error loading bomb.jpg" << std::endl;
	this->setTexture(bTexture);
}
Bomb::~Bomb()
{

}