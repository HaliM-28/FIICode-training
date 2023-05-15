#include "core.h"

void element::Draw(float x, float& y) {
	cout << "Nu cred ca ar trebui sa se ajunga aici\n";
}

Text::Text(std::string str) {
	txt.setString(str);
}
Text::Text() {
	txt.setString("Text");
}
void Text::Draw(float x, float& y) {
	cout << "Text\n";
}

void Imagine::Draw(float x, float& y) {
	cout << "Imagine\n";
}

folder::folder() {
	txt = *(new sf::Texture());
	txt.loadFromFile("samples/folder.png");
	rct.setSize({ (float)txt.getSize().x, (float)txt.getSize().y });
	rct.setPosition({ 0, 50 });
	rct.setTexture(&txt);
	nume = createText(rct.getPosition().x + 30, rct.getPosition().y + rct.getSize().y - 75, "folder");

	sizeX = rct.getSize().x;
	sizeY = rct.getSize().y;

	lastX = 0;
	lastY = 50;

	//inauntru.push_back(new Text);
}
void folder::Draw(float x, float &y) {
	rct.setPosition({ x, y });
	lastX = x;
	lastY = y;

	if (folderSelectat == this) {
		rct.setFillColor(sf::Color::Red);
	}

	draw(rct);
	win.draw(nume);

	if (folderSelectat == this) {
		rct.setFillColor(sf::Color::White);
	}

	for (vector<element*>::iterator i = inauntru.begin(); i != inauntru.end(); i++) {
		(*i)->Draw(x + rct.getSize().x, y);
		if (i != prev(inauntru.end()) )
			y += rct.getSize().y;
	}
}
void folder::createNew() {
	inauntru.push_back(new folder);
	//cout << "Hello\n";
}

copac::copac() {
	v = new folder();
	folderSelectat = v;
}
void copac::Draw(float x, float y) {
	v->Draw(x, y);
}

folder* folderSelectat;

void copac::FindUtil(sf::Vector2f& unde, folder* curent) {
	if (curent->lastX < unde.x && curent->lastX + curent->sizeX > unde.x &&
		curent->lastY < unde.y && curent->lastY + curent->sizeY > unde.y) {
		folderSelectat = curent;
	}
	else {
		for (auto i : curent->inauntru) {
			if (dynamic_cast<folder*>(i) != nullptr) {
				FindUtil(unde, dynamic_cast<folder*>(i));
			}
		}
	}
}