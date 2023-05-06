#pragma once

#include "RenderWindow.h"

int offX = 0, offY = 0;
extern sf::RenderWindow win;

void draw(sf::RectangleShape &rct) {
	
	// OFFING X, Y
	rct.setPosition(rct.getPosition().x + offX, rct.getPosition().y + offY);
	
	win.draw(rct);

	
	// DEOFFING X, Y
	rct.setPosition(rct.getPosition().x - offX, rct.getPosition().y - offY);
}