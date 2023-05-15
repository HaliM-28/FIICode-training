#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "RenderWindow.h"
#include "Draw.h"
#include "core.h"
#include "Font.h"

using namespace std;

class buton {
public:
	sf::RectangleShape btn;
	buton() {
		btn.setSize({ 50.0f, 50.0f });
		btn.setPosition(200, 0);
		btn.setFillColor(sf::Color::Red);
	}
	virtual void press() {
		// fa firsclick global in header seprat sa nu fut degeaba procesoru de fiecare data
		static bool firstClick = 1;

		float btnX = btn.getPosition().x;
		float btnY = btn.getPosition().y;
		sf::Vector2i real = { 0, 0 };
		sf::Vector2f real2 = btn.getSize();

		if (sf::Mouse::getPosition(win).x >= real.x && sf::Mouse::getPosition(win).x < real2.x &&
			sf::Mouse::getPosition(win).y >= real.y && sf::Mouse::getPosition(win).y < real2.y) {

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && firstClick == 1) {
				firstClick = 0;
				// aici deabia...
				folderSelectat->createNew();
			}
		}
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			firstClick = 1;
	}
	virtual void Draw() {
		btn.setPosition(win.mapPixelToCoords({ 0, 0 }, view1));
		btn.setScale({1.0f / zoom, 1.0f / zoom});
		win.draw(btn);
	}
};

class a {
public:
	virtual void f(float x, float& y) {
		cout << "A\n";
	};
};
class b : public a {
public:
	void f(float x, float &y) {
		cout << "B\n";
	};
};

int main() {
	font_init();
	/* folositor pt open existing
	filesystem searching everything:
	string path = "samples";
	for (const auto& entry : filesystem::directory_iterator(path)) {
		cout << entry.is_directory() << ' ' << entry.path() << '\n';
	}
	*/
	copac cp;
	buton btn;

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
				if (ev.mouseWheelScroll.delta > 0 && zoom < 3)
					view1.zoom(0.8), zoom /= 0.8;
				else
					if (ev.mouseWheelScroll.delta < 0 && zoom > 0.05)
						view1.zoom(1.25), zoom /= 1.25;
				
			}
			else if (ev.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i t = sf::Mouse::getPosition(win);
				sf::Vector2f t2 = win.mapPixelToCoords(t, view1);
				//cout << t2.x << ' ' << t2.y << '\n';
				cp.Find(t2);
			}
		}

		btn.press();

		win.clear(sf::Color::Black);

		btn.Draw();
		cp.Draw();

		win.display();
	}

	return 0;
}