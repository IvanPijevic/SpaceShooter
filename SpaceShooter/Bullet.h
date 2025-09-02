#ifndef BULLET_H
#define BULLET_H

#include <vector>

#include "DataStructures.h"
#include "Draw.h"
#include "Agent.h"

class Bullet
{
public:
	Bullet(Position position, Direction direction, float damage, float speed);
	~Bullet();

	void update();

	void draw(Size windowSize, std::vector<CHAR_INFO>& buffer);

	//TODO fix collision function (const Agent& agent, const Bullet& bullet??)
	//duplanje iste funkcije (Player i Bullet)
	bool colideWithAgent(const Agent& agent);

	int getLifeTime() const { return m_lifeTime; }
	float getDamage() const { return m_damage; }
	Position getPosition() const { return m_position; }

private:
	float m_damage;
	int m_lifeTime;

	Position m_position;
	Direction m_direction;

	float m_speed;

	Draw m_draw;

	wchar_t m_laser;
};

#endif  //BULLET_H