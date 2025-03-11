#include "Bullet.h"

Bullet::Bullet(Position pos, Direction dir, float speed, int lifeTime, int damage) :
	m_position(pos),
	m_direction(dir),
	m_speed(speed),
	m_lifeTime(lifeTime),
	m_damage(damage)
{
}

Bullet::~Bullet()
{
}

//void Bullet::update(int screenHeight, float deltaTime)
//{
//	m_position += m_direction * m_speed * deltaTime;
//	m_lifeTime--;
//
//	if (screenHeight / 2 < m_position.y)
//	{
//		m_lifeTime = 0;
//	}
//}
//
//bool Bullet::colideWithAgent(Agent* agent)
//{
//	Position enemyPosition = agent->getPosition();
//	int enemyWidth = agent->getWidth();
//	int enemyHeight = agent->getHeigh();
//
//	if (m_position.x > enemyPosition.x && m_position.x < enemyPosition.x + enemyWidth
//		&& m_position.y > enemyPosition.y && m_position.y < enemyPosition.y + enemyHeight)
//	{
//		return true;
//	}
//
//	return false;
//}