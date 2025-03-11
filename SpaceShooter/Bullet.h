#ifndef BULLET_H
#define BULLET_H

#include "DataStructures.h"

class Agent;

class Bullet
{
public:
	Bullet(Position pos, Direction dir, float speed, int lifeTime, int damage);
	~Bullet();

	void update();
	bool colideWithAgent(Agent* agent);

	//void draw();

	//Getters


private:
	Position m_position;
	Direction m_direction;

	float m_speed;
	int m_lifeTime;
	int m_damage;
};

#endif  //BULLET_H