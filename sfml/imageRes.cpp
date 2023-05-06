#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "RenderWindow.h"
#include "Draw.h"

using namespace std;

void onClickUpdate() {
	extern sf::RenderWindow win;
	extern int offX, offY;
	
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

	int curentX = sf::Mouse::getPosition(win).x;
	int curentY = sf::Mouse::getPosition(win).y;

	offX += (curentX - initX);
	offY += (curentY - initY);

	initX = curentX;
	initY = curentY;
}

int main() {

	sf::RectangleShape rct;
	rct.setFillColor(sf::Color::Yellow);
	rct.setSize({ 100, 200 });
	rct.setPosition({ 0, 50 });

	extern sf::RenderWindow win;
	
	while (win.isOpen()) {
		sf::Event ev;
		while (win.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				win.close();
			}
			else if (ev.type == sf::Event::MouseWheelScrolled) {
				//cout << "X, Y: " << ev.mouseWheelScroll.x << ' ' << ev.mouseWheelScroll.y << '\n';
				//cout << "Delt: " << ev.mouseWheelScroll.delta << '\n';
				
				// zoom it lol
				
			}
		}

		onClickUpdate();

		win.clear(sf::Color::Black);

		draw(rct);

		win.display();
	}

	return 0;
}