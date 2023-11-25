#pragma once 
#include  "SFML/Graphics.hpp" 
#include "node.h"
#include <list>

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Board {
private:
	std::list<Node> m_grid;
	sf::RenderWindow m_window;
	bool m_canMove = true;
	void drawUI();
	void setup();
	void captureKeyboardInput();
	void fillGrid();
	void spawnTile();
	void refresh();
	void move(Direction dir);
public:
	Board();
};