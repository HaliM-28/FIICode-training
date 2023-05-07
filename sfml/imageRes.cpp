#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "RenderWindow.h"
#include "Draw.h"

using namespace std;

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
				if (ev.mouseWheelScroll.delta > 0)
					view1.zoom(0.8), zoom /= 0.8;
				else
					view1.zoom(1.25), zoom /= 1.25;
				
			}
		}
		

		win.clear(sf::Color::Black);
		
		draw(rct);

		win.display();
	}

	return 0;
}