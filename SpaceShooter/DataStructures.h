#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <windows.h>

struct Position
{
	Position() : x(0), y(0) {}
	Position(short X, short Y) : x(X), y(Y) {}
	short x;
	short y;
};

struct Direction
{
	Direction() : x(0), y(0) {}
	Direction(short X, short Y) : x(X), y(Y) {}

	short x;
	short y;
};

struct Size
{
	Size(short X, short Y) : x(X), y(Y) {}
	short x;
	short y;

	operator COORD() const
	{
		return { x, y };
	}
};

#endif  //DATASTRUCTURES_H