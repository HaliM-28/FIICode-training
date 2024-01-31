#pragma once
#include <SFML/Graphics.hpp>
class text
{
public:
	text();
	void setPosition(sf::Vector2f);
	void setSize(sf::Vector2f);
private:
	sf::Text txt;
	sf::Font font;


};