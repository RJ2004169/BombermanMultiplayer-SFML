#pragma once
#include <SFML/Graphics.hpp>

class Bomb : public sf::Sprite
{
public:
	Bomb();
	~Bomb();
private:
	sf::Texture bTexture;
};