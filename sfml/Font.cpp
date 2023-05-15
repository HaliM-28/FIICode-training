#include "Font.h"

#include <SFML/Graphics.hpp>

sf::Font font;

void font_init() {
	font = *(new sf::Font);
	font.loadFromFile("samples/font/8-bit-font.ttf");
}

sf::Text createText(float x, float y, std::string str) {
	sf::Text t;
	t.setFont(font);
	t.setString(str);
	t.setCharacterSize(30);
	t.setFillColor(sf::Color::White);
	t.setPosition({ x, y });
	return t;
};
