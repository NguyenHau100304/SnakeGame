#pragma once
#include "Segment.h"
#define EDGE 30
#define MAX_COLUMN 1200
#define MAX_ROW 840


enum MOVE {
	UP, DOWN, LEFT, RIGHT
};



class Snake
{
private:
	SEGMENT* head;
	SEGMENT* tail;
	int size;
	static const int dx[4];
	static const int dy[4];
public:
	Snake(COORD);
	~Snake();
	void clear();
	int getSize();
	SEGMENT* getHead();
	SEGMENT* getTail();
	void append();
	bool move(MOVE movi);
	//Iterator for List
	class Iterator {
		SEGMENT* current;
	public:
		Iterator(SEGMENT* _curr);
		Iterator& operator++();
		SEGMENT& operator*();
		bool operator!=(const Iterator& other);
	};

	Iterator begin();
	Iterator end();
};





const int Snake::dx[4] = {0, 0, -30, 30};
const int Snake::dy[4] = { -30, 30, 0, 0 };


Snake::Snake(COORD coord) {
	head = tail = new SEGMENT(coord, nullptr);
	size = 1;
}
Snake::~Snake() {
	SEGMENT* current = head;
	while (current) {
		SEGMENT* temp = current;
		current = current->next;
		delete temp;
	}
	size = 0;
}
void Snake::clear() {
	SEGMENT* current = head;
	while (current) {
		SEGMENT* temp = current;
		current = current->next;
		delete temp;
	}
	size = 0;
}
int Snake::getSize() {
	return size;
}
SEGMENT* Snake::getHead() {
	return head;
}
SEGMENT* Snake::getTail() {
	return tail;
}

bool Snake::move(MOVE movi) {
	COORD previous = head->getCoord();
	head->getCoord().add(dx[movi],dy[movi]);
	if (head->getCoord().getX() >= MAX_COLUMN)
		head->getCoord().setX(0);
	if (head->getCoord().getY() >= MAX_ROW)
		head->getCoord().setY(0);
	if (head->getCoord().getX() < 0)
		head->getCoord().setX(MAX_COLUMN - EDGE);
	if (head->getCoord().getY() < 0)
		head->getCoord().setY(MAX_ROW - EDGE);

	for (Snake::Iterator it = Iterator(head->next); it != end(); ++it) {
		COORD temp = (*it).coord;
		(*it).coord = previous;
		previous = temp;
		if ((*it).coord.getX() == head->getCoord().getX() && (*it).coord.getY() == head->getCoord().getY())
			return false;
	}
	return true;
}
void Snake::append() {
	SEGMENT* newTail = new SEGMENT(tail->getCoord(), nullptr);
	tail->next = newTail;
	tail = newTail;
	++size;
}


Snake::Iterator::Iterator(SEGMENT* _curr) : current(_curr) {}
Snake::Iterator& Snake::Iterator::operator++() {
	if (current != nullptr) {
		current = current->next;
	}
	return *this;
}
SEGMENT& Snake::Iterator::operator*() {
	return *(current);
}
bool Snake::Iterator::operator!=(const Iterator& other) {
	return current != other.current;
}


Snake::Iterator Snake::begin() {
	return Iterator(head);
}
Snake::Iterator Snake::end() {
	return Iterator(nullptr);
}