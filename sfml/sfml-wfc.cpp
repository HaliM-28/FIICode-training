#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <set>
#include <queue>
#include <thread>
#include <algorithm>

#include <SFML/Graphics.hpp>

sf::Image im;
sf::Vector2u size;

int ii[] = { 0, 0, 1, -1 };
int jj[] = { -1, 1, 0, 0 };

struct bucata {
	sf::Color **px;
	sf::Uint8* image_pixels;
	sf::Image im;
	sf::Texture txt;
	sf::Sprite spr;
	std::vector<bucata*> 
		potrivireSus,
		potrivireJos,
		potrivireSt,
		potrivireDr;
	std::pair<int, int> stSus;
	bucata* get_this() {
		return this;
	}
};
std::vector<bucata> bucati;
int cnt_bucata = 4;
const unsigned int mapaX = 25, mapaY = 25;
std::string path = "samples/floare5.png";
bool imparteContinuaImaginea = 0;
int imparteCateSkip = 0;
std::vector<bucata*> mapa[mapaX][mapaY] = { {} };

bucata inutil;

void intersectareMultimi(std::vector<bucata*>& a, std::vector<bucata*>& b) { // a se va scurta sau va ramane la fel
	std::vector<int> ceSterg;
	int cnt = 0;
	for (auto& i : a) {
		bool ok = 0;
		for (auto& j : b) {
			if (i == j) ok = 1;
		}
		if (ok == 1);
		else ceSterg.push_back(cnt);
		cnt++;
	}
	for (int i = ceSterg.size() - 1; i >= 0; i--) {
		a.erase(a.begin() + ceSterg[i]);
	}
}

bool pozOk(int x, int y) {
	if (x >= 0 && y >= 0 && x < mapaX && y < mapaY) {
		return 1;
	}
	return 0;
}

void propagate(int x, int y) {
	for (int k = 0; k < 4; k++) {
		unsigned int ni = ii[k] + x;
		unsigned int nj = jj[k] + y;
		if (pozOk(ni, nj) && mapa[ni][nj].size() > 1) {
			switch (k) {
			case 0:
				intersectareMultimi(mapa[ni][nj], mapa[x][y][0]->potrivireSt);
				break;
			case 1:
				intersectareMultimi(mapa[ni][nj], mapa[x][y][0]->potrivireSus);
				break;
			case 2:
				intersectareMultimi(mapa[ni][nj], mapa[x][y][0]->potrivireDr);
				break;
			case 3:
				intersectareMultimi(mapa[ni][nj], mapa[x][y][0]->potrivireJos);
				break;
			}
		}
	}
}

void initBucatiPixels() {
	bool ok = 0;
	for (auto& k : bucati) {
		k.image_pixels = new sf::Uint8[cnt_bucata * cnt_bucata * 4];
		for (int i = 0; i < cnt_bucata; i++) {
			for (int j = 0; j < cnt_bucata; j++) {
				k.image_pixels[4 * (i * cnt_bucata + j) + 0] = k.px[i][j].r;
				k.image_pixels[4 * (i * cnt_bucata + j) + 1] = k.px[i][j].g;
				k.image_pixels[4 * (i * cnt_bucata + j) + 2] = k.px[i][j].b;
				k.image_pixels[4 * (i * cnt_bucata + j) + 3] = 255;
			}
		}
		k.txt.create(cnt_bucata, cnt_bucata);
		k.txt.update(k.image_pixels);

		k.spr.setTexture(k.txt);
		k.spr.setScale({ 10.0f, 10.0f });
	}

}

void creeazaBucata(int st, int sus) {
	bucata cur;
	cur.px = new sf::Color *[cnt_bucata];
	for (int i = 0; i < cnt_bucata; i++) cur.px[i] = new sf::Color[cnt_bucata];

	for (int j = sus; j < sus + cnt_bucata; j++) {
		for (int i = st; i < st + cnt_bucata; i++) {
			cur.px[j-sus][i-st] = im.getPixel(i % size.x, j % size.y);
		}
	}

	cur.stSus = {sus, st};
	bucati.push_back(cur);
}

void imparte(bool continuaImaginea = 1, int cateSkip = 0) { // daca fac patratelele doar pe imaginea normala, sau ii dau repeat ca sa ma mia multe optiuni
	continuaImaginea = 1 - continuaImaginea; // ca sa mearga for-ul

	for (int j = 0; j < size.y - (continuaImaginea * cnt_bucata) + continuaImaginea; (cateSkip == 0 ? j++ : j+=cateSkip) ) {
		for (int i = 0; i < size.x - (continuaImaginea * cnt_bucata) + continuaImaginea; (cateSkip == 0 ? i++ : i += cateSkip) ) {
			creeazaBucata(i, j);
		}
	}
}


struct elem {
	int entr = 10000000;
	sf::Vector2u poz;
};
class Compare
{
public:
	bool operator() (elem a, elem b) {
		if (b.entr < a.entr) return true;
		else return false;
	}
};

int main() {
	srand(time(NULL));

	sf::RenderWindow win(sf::VideoMode(1200, 800), "nume_fain");
	
	im.loadFromFile(path);
	sf::Sprite spr;
	sf::Texture txt;
	txt.loadFromImage(im);
	spr.setTexture(txt);
	size = im.getSize();
	if (1 == 0)
	for (int i = 0; i < size.y; i++) {
		for (int j = 0; j < size.x; j++) {
			if (im.getPixel(i, j).b > 10)
				im.setPixel(i, j, sf::Color::Cyan);
		}
	}

	imparte(imparteContinuaImaginea, imparteCateSkip); // sa le si rotesc? | scoate duplicatele

	/*
	* verific bucatile in parte
	int cnt = 0;
	for (auto &k : bucati) {
		std::cout << '\n' << cnt++ <<  ' ' << k.stSus.first << ' ' << k.stSus.second << '\n';
		for (int i = 0; i < cnt_bucata; i++) {
			for (int j = 0; j < cnt_bucata; j++) {
				if (k.px[i][j].b == 0) std::cout << "  ";
				std::cout << (int)k.px[i][j].b << ' ';
			}
			std::cout << '\n';
		}
	}
	*/

	for (auto k = bucati.begin(); k != bucati.end(); k++) {
		sf::Color* urm = new sf::Color[cnt_bucata];

		// dreapta
		for (int i = 0; i < cnt_bucata; i++) {
			urm[i] = im.getPixel((k->stSus.second + cnt_bucata) % size.x, (k->stSus.first + i) % size.y);
		}
		for (auto t = bucati.begin(); t != bucati.end(); t++) {
			bool ok = 1;
			for (int i = 0; i < cnt_bucata; i++) {
				if (urm[i] != t->px[i][0]) ok = 0;
			}
			if (ok == 1) {
				//std::cout << "Pentru " << k->stSus.first << ' ' << k->stSus.second << "   merge " << t->stSus.first << ' ' << t->stSus.second << '\n';
				k->potrivireDr.push_back(t->get_this());
				//std::cout << "Pentru " << k->stSus.first << ' ' << k->stSus.second << "   merge " << t->stSus.first << ' ' << t->stSus.second << '\n';
			}
		}

		// sus
		for (int i = 0; i < cnt_bucata; i++) {
			urm[i] = im.getPixel((k->stSus.second + i) % size.x, (k->stSus.first - 1 + size.y) % size.y);
		}
		for (auto t = bucati.begin(); t != bucati.end(); t++) {
			bool ok = 1;
			for (int i = 0; i < cnt_bucata; i++) {
				if (urm[i] != t->px[cnt_bucata - 1][i]) ok = 0;
			}
			if (ok == 1) {
				//std::cout << "Pentru " << k->stSus.first << ' ' << k->stSus.second << "   merge " << t->stSus.first << ' ' << t->stSus.second << '\n';
				k->potrivireSus.push_back(t->get_this());
				//std::cout << "Pentru " << k->stSus.first << ' ' << k->stSus.second << "   merge " << t->stSus.first << ' ' << t->stSus.second << '\n';
			}
		}

		// stanga
		for (int i = 0; i < cnt_bucata; i++) {
			urm[i] = im.getPixel((k->stSus.second - 1 + size.x) % size.x, (k->stSus.first + i) % size.y);
		} 
		for (auto t = bucati.begin(); t != bucati.end(); t++) {
			bool ok = 1;
			for (int i = 0; i < cnt_bucata; i++) {
				if (urm[i] != t->px[i][cnt_bucata - 1]) ok = 0;
			}
			if (ok == 1) {
				//std::cout << "Pentru " << k->stSus.first << ' ' << k->stSus.second << "   merge " << t->stSus.first << ' ' << t->stSus.second << '\n';
				k->potrivireSt.push_back(t->get_this());
			}
		}

		// jos
		for (int i = 0; i < cnt_bucata; i++) {
			urm[i] = im.getPixel((k->stSus.second + i) % size.x, (k->stSus.first + cnt_bucata) % size.y);
		}
		for (auto t = bucati.begin(); t != bucati.end(); t++) {
			bool ok = 1;
			for (int i = 0; i < cnt_bucata; i++) {
				if (urm[i] != t->px[0][i]) ok = 0;
			}
			if (ok == 1) {
				//std::cout << "Pentru " << k->stSus.first << ' ' << k->stSus.second << "   merge " << t->stSus.first << ' ' << t->stSus.second << '\n';
				
				k->potrivireJos.push_back(t->get_this());
			}
		}

	}

	initBucatiPixels();


	inutil.image_pixels = new sf::Uint8[cnt_bucata * cnt_bucata * 4];
	for (int i = 0; i < cnt_bucata; i++) {
		for (int j = 0; j < cnt_bucata; j++) {
			inutil.image_pixels[4 * (i * cnt_bucata + j) + 0] = 0;
			inutil.image_pixels[4 * (i * cnt_bucata + j) + 1] = 255;
			inutil.image_pixels[4 * (i * cnt_bucata + j) + 2] = 255;
			inutil.image_pixels[4 * (i * cnt_bucata + j) + 3] = 255;
		}
	}
	inutil.txt.create(cnt_bucata, cnt_bucata);
	inutil.txt.update(inutil.image_pixels);
	inutil.spr.setTexture(inutil.txt);
	inutil.spr.setScale({ 10.0f, 10.0f });


	std::vector<bucata*> normal;
	for (auto& i : bucati) normal.push_back(&i);



	std::priority_queue < elem, std::vector<elem>, Compare> pq;
	pq.push({ (int)normal.size(), sf::Vector2u(rand() % mapaX, rand() % mapaY)});

	// {&bucati[rand() % bucati.size()]}

	for (int i = 0; i < mapaX; i++) {
		for (int j = 0; j < mapaY; j++) {
			mapa[i][j] = normal;
		}
	}

	sf::Event ev;
	while (win.isOpen()) {
		while (win.pollEvent(ev)) {
			switch (ev.type) {
			case sf::Event::Closed:
				win.close();
				break;
			}
		}
		win.clear(sf::Color::Magenta);

		if (1==0)
		if (pq.size() != 0) {

			elem top = pq.top();
			pq.pop();

			//std::cout << top.poz.x << ' ' << top.poz.y << '\n';

			if (mapa[top.poz.x][top.poz.y].size() == 0) { // nu merge nimic
				// pun doar bleu peste tot
				mapa[top.poz.x][top.poz.y].push_back(&inutil);
			}
			else if (mapa[top.poz.x][top.poz.y].size() > 1) { // am variante
				int indice = rand() % mapa[top.poz.x][top.poz.y].size();
				bucata* t = mapa[top.poz.x][top.poz.y][indice];
				mapa[top.poz.x][top.poz.y].clear();
				mapa[top.poz.x][top.poz.y].push_back(t);

				//std::cout << "Pun: " << t->stSus.first << ' ' << t->stSus.second << '\n';
				//for (auto i : t->potrivireDr) {
				//	std::cout << "La dreapta: " << i->stSus.first << ' ' << i->stSus.second << '\n';
				//}

				// propagate around
				propagate(top.poz.x, top.poz.y);
			}

			for (int k = 0; k < 4; k++) {
				unsigned int ni = ii[k] + top.poz.x;
				unsigned int nj = jj[k] + top.poz.y;
				if (pozOk(ni, nj) && mapa[ni][nj].size() != 1) {
					//std::cout << "Adaug: " << ni << ' ' << nj << '\n';
					pq.push({ (int)mapa[ni][nj].size(), sf::Vector2u(ni, nj) });
				}
			}


		}

		for (int i = 0; i < mapaX; i++) {
			for (int j = 0; j < mapaY; j++) {
				if (mapa[i][j].size() == 1) {
					mapa[i][j][0]->spr.setPosition({(float)j * 10 * cnt_bucata, (float)i * 10 * cnt_bucata});
					win.draw(mapa[i][j][0]->spr);
				}
			}
		}


		int cnt = 0;
		for (auto &i : bucati) {
			i.spr.setPosition(0, cnt);
			win.draw(i.spr);

			int cnt2 = 10 * cnt_bucata + 3;
			for (auto& j : i.potrivireDr) {
				j->spr.setPosition(cnt2, cnt);
				cnt2 += 10 * cnt_bucata + 3;
				win.draw(j->spr);
			}

			cnt += 10 * cnt_bucata + 3;
		}

		win.display();

		//system("pause");
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}



	return 0;
}