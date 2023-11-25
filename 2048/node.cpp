#include "node.h"

Node::Node(int x, int y, int state) {
	m_x = x;
	m_y = y;
	m_state = state;
	m_posX = 15 + 147 * (x - 1);
	m_posY = 119 + 147 * (y - 1);
}

int Node::getX() {
	return m_x;
}

int Node::getY() {
	return m_y;
}

int Node::getPosX() {
	return m_posX;
}

int Node::getPosY() {
	return m_posY;
}

int Node::getState() {
	return m_state;
}

bool Node::getSpawnedStatus() {
	return m_wasSpawned;
}

void Node::setX(int x) {
	m_x = x;
}

void Node::setY(int y) {
	m_y = y;
}

void Node::setState(int newState) {
	m_state = newState;
}

void Node::setSpawnStatus(bool spawnState) {
	m_wasSpawned = spawnState;
}

void Node::insert(std::list<Node>& l, int xSearch, int ySearch, int new_state) {
	for (auto it = l.rbegin(); it != l.rend(); it++) {
		if (it->m_x == xSearch && it->m_y == ySearch) {
			it->m_state = new_state;
			return;
		}
	}
}