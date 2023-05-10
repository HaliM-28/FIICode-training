#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "RenderWindow.h"
#include "Draw.h"

using namespace std;

class element {
public:
	virtual void Draw() {
		cout << "Nu cred ca ar trebui sa se ajunga aici\n";
	}
};
class Text : public element {
public:
	sf::Text txt;
	Text(std::string str) {
		txt.setString(str);
	}
	Text() {
		txt.setString("Text");
	}
	void Draw() {
		cout << "Text\n";
	}
};
class Imagine : public element {
public:
	sf::Image im;
	void Draw() {
		cout << "Imagine\n";
	}
};
class folder : public element {
public:
	sf::RectangleShape rct;
	sf::Texture txt;
	vector<element*> inauntru;

	folder() {
		txt = *(new sf::Texture());
		txt.loadFromFile("samples/folder.png");
		rct.setSize({ (float)txt.getSize().x, (float)txt.getSize().y});
		rct.setPosition({ 0, 50 });
		rct.setTexture(&txt);

		inauntru.push_back(new Text);
	}
	void Draw(float x, float y) {
		rct.setPosition({ x, y });
		draw(rct);
		for (auto i : inauntru) {
			i->Draw();
		}
	}
};
class copac {
private:
	folder* v;
public:
	copac() {
		v = new folder();
	}
	void Draw() {
		v->Draw(0, 0);
	}
};

int main() {
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