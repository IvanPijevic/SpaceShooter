#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <windows.h>

struct Direction
{
	Direction() : x(0), y(0) {}
	Direction(short X, short Y) : x(X), y(Y) {}

	Direction operator*(float num) const
	{
		return Direction(static_cast<short>(x * num), static_cast<short>(y * num));
	}

	short x;
	short y;
};

struct Position
{
	Position() : x(0), y(0) {}
	Position(float X, float Y) : x(X), y(Y) {}

	Position operator*(const Direction& direction) const
	{
		return Position(x * direction.x, y * direction.y);
	}

	Position operator+(const Direction& direction) const
	{
		return Position(x + direction.x, y + direction.y);
	}

	Position& operator+=(const Direction& direction)
	{
		x += direction.x;
		y += direction.y;
		return *this;
	}

	float x;
	float y;
};

struct Size
{
	Size(short Width, short Height) : width(Width), height(Height) {}
	short width;
	short height;

	operator COORD() const
	{
		return { width, height };
	}
};

//Enemy spec
enum class TRAJECTORY
{
	LINE, DOUBLE_LINE, CIKCAK
};

enum class ENEMY_TYPE
{
	DRONE, BATTLE_SHIP
};

struct LevelData
{
	int numberOfShips;
	ENEMY_TYPE enemyType;
	TRAJECTORY trajectory;
};


#endif  //DATASTRUCTURES_H