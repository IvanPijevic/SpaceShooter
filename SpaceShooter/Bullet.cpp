#include "Bullet.h"

Bullet::Bullet(Position position, Direction direction, float damage, float speed) :
	m_position(position),
	m_direction(direction),
	m_damage(damage),
	m_speed(speed),
	m_laser(L'-'),
	m_lifeTime(100)
{

}

Bullet::~Bullet()
{ }

void Bullet::update()
{
	m_position += m_direction * m_speed;
	m_lifeTime--;
}

void Bullet::draw(Size windowSize, std::vector<CHAR_INFO>& buffer)
{
	m_draw.drawPixel(m_position.x, m_position.y, m_laser, FOREGROUND_RED | FOREGROUND_INTENSITY, windowSize, buffer);
}

bool Bullet::colideWithAgent(const Agent& agent)
{
	Position enemyPosition = agent.getPosition();
	short enemyWidth = agent.getWidth();
	short enemyHeight = agent.getHeight();

	if (m_position.x < enemyPosition.x + enemyWidth && m_position.x + enemyWidth > enemyPosition.x
		&& m_position.y < enemyPosition.y + enemyHeight && m_position.y + enemyHeight > enemyPosition.y)
	{
		return true;
	}

	return false;
}