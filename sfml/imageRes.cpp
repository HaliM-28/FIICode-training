#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

using namespace std;

int main() {

	sf::RectangleShape rct;
	rct.setFillColor(sf::Color::Yellow);
	rct.setSize({ 100, 200 });
	rct.setPosition({ 0, 50 });

	sf::RenderWindow win(sf::VideoMode(800, 600), "Win");
	
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

		win.clear(sf::Color::Black);

		win.draw(rct);

		win.display();
	}

	return 0;
}