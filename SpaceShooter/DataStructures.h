#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

struct Position
{
	Position() : x(0), y(0) {}
	Position(short X, short Y) : x(X), y(Y) {}
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