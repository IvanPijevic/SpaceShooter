#include "Weapon.h"

Weapon::Weapon(std::string name, int fireRate, int bulletsPerShot, 
	float bulletDamage, float bulletSpeed) :
	m_name(name),
	m_fireRate(fireRate),
	m_bulletsPerShot(bulletsPerShot),
	m_bulletDamage(bulletDamage),
	m_bulletSpeed(bulletSpeed)
{}

void Weapon::update(bool isSpaceDown, const Position& position, const Direction& direction, std::vector<Bullet>& bullets)
{
	m_frameCounter++;
	if (m_frameCounter >= m_fireRate && isSpaceDown)
	{
		fire(position, direction, bullets);
		m_frameCounter = 0;
	}
}

void Weapon::fire(const Position& position, const Direction& direction, std::vector<Bullet>& bullets)
{
	std::generate_n(std::back_inserter(bullets), m_bulletsPerShot, [&]()
		{
			return Bullet(position, direction, m_bulletDamage, m_bulletSpeed);
		});
}