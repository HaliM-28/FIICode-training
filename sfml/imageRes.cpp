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
	sf::Texture texture;
	sf::RectangleShape btn;
	buton() {
		;
	}
	virtual void press() {
		;
	}
	virtual void Draw() {
		;
	};
};

class buton_folder : public buton {
public:
	buton_folder() {
		texture.loadFromFile("samples/folder.png");
		btn.setTexture(&texture);

		btn.setSize({ 50.0f, 50.0f });
		btn.setPosition(0, 0);
		btn.setFillColor(sf::Color::Red);
	}
	void press() {
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
	void Draw() {
		btn.setPosition(win.mapPixelToCoords({ 0, 0 }, view1));
		btn.setScale({ 1.0f / zoom, 1.0f / zoom });
		win.draw(btn);
	}
};

class buton_text : public buton {
public:
	buton_text() {
		texture.loadFromFile("samples/text.png");
		btn.setTexture(&texture);

		btn.setSize({ 50.0f, 50.0f });
		btn.setPosition(50, 0);
	}
	void press() {
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
	void Draw() {
		btn.setPosition(win.mapPixelToCoords({ 50, 0 }, view1));
		btn.setScale({ 1.0f / zoom, 1.0f / zoom });
		win.draw(btn);
	}
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
	buton_folder btn_fol;
	buton_text btn_txt;

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

		btn_fol.press();
		btn_txt.press();

		win.clear(sf::Color::Black);

		btn_fol.Draw();
		btn_txt.Draw();
		cp.Draw();

		win.display();
	}

	return 0;
}