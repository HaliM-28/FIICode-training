#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "RenderWindow.h"
#include "Draw.h"

using namespace std;

class element {
public:
	virtual void Draw();
};

class Text : public element {
public:
	sf::Text txt;
	Text(std::string str);
	Text();
	void Draw();
};

class Imagine : public element {
public:
	sf::Image im;
	void Draw();
};

class folder : public element {
public:
	sf::RectangleShape rct;
	sf::Texture txt;
	vector<element*> inauntru;

	folder();
	void Draw(float x, float y);
	void createNew();
};

class copac {
private:
	folder* v;
public:
	copac();
	void Draw();
};

extern folder* folderSelectat;