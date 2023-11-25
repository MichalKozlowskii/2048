#pragma once
#include <list>

class Node {
private:
	int m_x, m_y, m_state, m_posX, m_posY;
	bool m_wasSpawned = false;
public:
	Node(int x, int y, int state);
	int getX();
	int getY();
	int getPosX();
	int getPosY();
	int getState();
	bool getSpawnedStatus();
	void setX(int x);
	void setY(int y);
	void setState(int newState);
	void setSpawnStatus(bool spawnState);
	void insert(std::list<Node>& l, int xSearch, int ySearch, int new_state);
};