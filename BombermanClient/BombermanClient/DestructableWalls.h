#pragma once
#include <SFML/Graphics.hpp>

class DestructableWalls : public sf::Sprite
{
public:
	DestructableWalls();
	~DestructableWalls();
private:
	sf::Texture wTexture;
};