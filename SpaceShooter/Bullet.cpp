#include "Bullet.h"

Bullet::Bullet(Position position, Direction direction, float damage, float speed) :
	m_position(position),
	m_direction(direction),
	m_damage(damage),
	m_speed(speed),
	m_laser(L'-')
{

}

Bullet::~Bullet()
{ }

void Bullet::update()
{
	m_position += m_direction * m_speed;
}

void Bullet::draw(Size windowSize, std::vector<CHAR_INFO>& buffer)
{
	m_draw.drawPixel(m_position.x, m_position.y, m_laser, FOREGROUND_RED | FOREGROUND_INTENSITY, windowSize, buffer);
}