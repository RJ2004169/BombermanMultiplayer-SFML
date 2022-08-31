#include "IndestructableWalls.h"
#include <iostream>

IndestructableWalls::IndestructableWalls()
{
	if (!wTexture.loadFromFile("Media/iwall.png"))
		std::cout << "Error loading iwall.png" << std::endl;
	this->setTexture(wTexture);
}
IndestructableWalls::~IndestructableWalls()
{

}