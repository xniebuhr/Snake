#pragma once
#include <SFML/Graphics.hpp>

class Wall
{
private:
	sf::RectangleShape wallShape;

public:
	Wall(sf::Vector2f position, sf::Vector2f size);

	sf::RectangleShape getShape();
};
