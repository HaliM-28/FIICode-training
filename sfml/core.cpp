#include "core.h"

void element::Draw() {
	cout << "Nu cred ca ar trebui sa se ajunga aici\n";
}

Text::Text(std::string str) {
	txt.setString(str);
}
Text::Text() {
	txt.setString("Text");
}
void Text::Draw() {
	cout << "Text\n";
}

void Imagine::Draw() {
	cout << "Imagine\n";
}

folder::folder() {
	txt = *(new sf::Texture());
	txt.loadFromFile("samples/folder.png");
	rct.setSize({ (float)txt.getSize().x, (float)txt.getSize().y });
	rct.setPosition({ 0, 50 });
	rct.setTexture(&txt);

	//inauntru.push_back(new Text);
}
void folder::Draw(float x, float y) {
	rct.setPosition({ x, y });

	if (folderSelectat == this) {
		rct.setFillColor(sf::Color::Red);
	}

	draw(rct);

	if (folderSelectat == this) {
		rct.setFillColor(sf::Color::White);
	}

	for (auto i : inauntru) {
		i->Draw();
	}
}
void folder::createNew() {
	cout << "Hello\n";
}

copac::copac() {
	v = new folder();
	folderSelectat = v;
}
void copac::Draw() {
	v->Draw(0, 0);
}

folder* folderSelectat;