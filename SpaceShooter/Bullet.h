#ifndef BULLET_H
#define BULLET_H

#include <vector>

#include "DataStructures.h"
#include "Draw.h"


class Bullet
{
public:
	Bullet(Position position, Direction direction, float damage, float speed);
	~Bullet();

	void update();

	void draw(Size windowSize, std::vector<CHAR_INFO>& buffer);

private:
	int m_damage;

	Position m_position;
	Direction m_direction;

	float m_speed;

	Draw m_draw;

	wchar_t m_laser;
};

#endif  //BULLET_H