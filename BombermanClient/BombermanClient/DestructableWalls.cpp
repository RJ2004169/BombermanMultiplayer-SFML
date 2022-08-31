#include "DestructableWalls.h"
#include <iostream>

DestructableWalls::DestructableWalls()
{
	if (!wTexture.loadFromFile("Media/dwall.jpg"))
		std::cout << "Error loading dwall.jpg" << std::endl;
	this->setTexture(wTexture);
}
DestructableWalls::~DestructableWalls()
{

}