#pragma once

class COORD {
	int x, y;
public:
	COORD(int _x = 0, int _y = 0) : x(_x), y(_y) {}
	COORD(const COORD& _coord) {
		x = _coord.x;
		y = _coord.y;
	}
	void add(int _x, int _y) {
		x += _x;
		y += _y;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	void setX(int _x) {
		x = _x;
	}
	void setY(int _y) {
		y = _y;
	}
};


class SEGMENT
{
	friend class Snake;
private:
	COORD coord;
	SEGMENT* next;
public:
	SEGMENT() : coord(), next(nullptr) {}
	SEGMENT(COORD _coord, SEGMENT* _next) : coord(_coord) {
		next = _next;
	}
	COORD& getCoord() {
		return coord;
	}
	void setCoord(COORD _coord) {
		coord = _coord;
	}
	SEGMENT* getNext() {
		return next;
	}
};

