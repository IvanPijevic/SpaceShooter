#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <vector>

#include "Bullet.h"

class Weapon
{
public:
	Weapon(std::string gunName, int fireRate, int bulletsPerShots, float bulletDamage, float bulletSpeed);
	~Weapon();

	void update(bool isKeyPressed, int bulletsPerShots, Position* position, Direction& direction, std::vector<Bullet>& bullets);


private:
	void fire(const Position& position, Direction& direction, std::vector<Bullet>& bullets);

private:
	std::string m_name;

	int fireRate;
	int m_bulletsPerShoot;
	int m_bulletDamage;

	float m_bulletSpeed;
	float m_frameCounter;
	float m_lifeTime;

	bool m_isFired;
};

#endif  //WEAPON_H