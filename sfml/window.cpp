#include "window.h"

sf::RenderWindow win(sf::VideoMode(600, 400), "Titlu");
float delta_time = 1.0f;

const unsigned int fps = 144;
const float milliseconds_frame = 1000.0f / float(fps);