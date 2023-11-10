#pragma once 
#include  "SFML/Graphics.hpp" 
#include <list>

class Board {
private:
	sf::RenderWindow m_window;
	void drawUI();
	void setup();
	void captureKeyboardInput();
public:
	Board();
};