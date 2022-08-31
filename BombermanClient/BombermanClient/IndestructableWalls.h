#pragma once
#include <SFML/Graphics.hpp>

class IndestructableWalls : public sf::Sprite
{
public:
	IndestructableWalls();
	~IndestructableWalls();
private:
	sf::Texture wTexture;
};