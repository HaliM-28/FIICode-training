#include "RenderWindow.h"
#include "Draw.h"

#include <SFML/Graphics.hpp>

float offX = 0, offY = 0;

void onClickUpdate() {
	extern sf::RenderWindow win;
	extern float zoom;
	offX = 0;
	offY = 0;

	static bool clicked = 0;
	static int initX = 0, initY = 0;

	if (clicked == 0) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			clicked = 1;
			initX = sf::Mouse::getPosition(win).x;
			initY = sf::Mouse::getPosition(win).y;
		}
		else {
			return;
		}
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		clicked = 0;
		return;
	}

	float curentX = sf::Mouse::getPosition(win).x;
	float curentY = sf::Mouse::getPosition(win).y;

	offX -= ((curentX - initX) * (float)(1 / zoom));
	offY -= ((curentY - initY) * (float)(1 / zoom));

	initX = curentX;
	initY = curentY;
}

void draw(sf::RectangleShape& rct) {
	extern sf::RenderWindow win;

	onClickUpdate();

	view1.move({ (float)offX, (float)offY });
	win.setView(view1);
	win.draw(rct);
}