#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "RenderWindow.h"
#include "Draw.h"

using namespace std;

class element {
public:
	virtual void Draw() {

	}
};
class folder : public element {
public:
	sf::RectangleShape rct;
	folder() {
		rct.setFillColor(sf::Color::Yellow);
		rct.setSize({ 100, 200 });
		rct.setPosition({ 0, 50 });
	}
	void Draw() {
		draw(rct);
	}
};
class copac {
private:
	vector<element*> v;
public:
	copac() {
		element* el;
		folder* fd = new folder();
		el = fd;
		v.push_back(el);
	}
	void Draw() {
		for (auto i : v) i->Draw();
	}
};

class base {
public:
	int x = 10;
	virtual void printX() {
		cout << x << "\n";
	}
};
class der : public base {
public:
	int y = 30;
	void printX() {
		cout << y << "\n";
	}
};

int main() {
	/*
	base* b;
	der d;
	b = &d;
	b->printX();
	*/
	copac cp;


	sf::RectangleShape rct;
	rct.setFillColor(sf::Color::Yellow);
	rct.setSize({ 100, 200 });
	rct.setPosition({ 0, 50 });

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
		
		//draw(rct);
		cp.Draw();

		win.display();
	}

	return 0;
}