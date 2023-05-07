#include "RenderWindow.h"

#include <SFML/Graphics.hpp>

float zoom = 1.0f;
sf::RenderWindow win(sf::VideoMode(800, 600), "Win");
sf::View view1(sf::FloatRect(0, 0, 800, 600));