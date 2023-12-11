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
	int m_points = 0;
	void drawUI();
	void setup();
	void captureKeyboardInput();
	void fillGrid();
	void spawnTile();
	void refresh();
	void addPoints(int amount);
	void move(Direction dir);
	bool isAbleToMove();
	bool hasWon();
	bool hasLost();
	void drawWinScreen();
	void drawLooseScreen();
public:
	Board();
};