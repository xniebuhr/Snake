#pragma once
#include <SFML/Graphics.hpp>

class Apple
{
private:
	sf::RectangleShape sprite;

public:
	Apple();

	void setPosition(sf::Vector2f newPosition);
	sf::RectangleShape getSprite();
};