#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include <SFML/Graphics.hpp>

#include "RenderWindow.h"
#include "Draw.h"
#include "Font.h"

using namespace std;

class element {
public:
	sf::Text nume;
	float lastX = 0, lastY = 0;
	float sizeX = 0, sizeY = 0;

	virtual void Draw(float x, float& y);
};

class Text : public element {
public:
	sf::Text txt;
	Text(std::string str);
	Text();
	void Draw(float x, float& y);
};

class Imagine : public element {
public:
	sf::Image im;
	void Draw(float x, float& y);
};

class folder : public element {
public:
	sf::RectangleShape rct;
	sf::Texture txt;
	vector<element*> inauntru;

	folder();
	void Draw(float x, float &y);
	void createNew();
};

class copac {
private:
	folder* v;

	void FindUtil(sf::Vector2f& unde, folder* curent);
public:
	copac();
	void Draw(float x = 0, float y = 0);
	void Find(sf::Vector2f unde) {
		FindUtil(unde, v);
	}
};

extern folder* folderSelectat;