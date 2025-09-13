#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#include "Bullet.h"

class Weapon
{
public:
	Weapon(std::string name, int fireRate, int bulletsPerShot, 
		float bulletDamage, float bulletSpeed);

	void update(bool isSpaceDown, const Position& position, const Direction& direction, std::vector<Bullet>& bullets);


private:
	void fire(const Position& position, const Direction& direction, std::vector<Bullet>& bullets);

private:
	int m_fireRate;
	int m_bulletsPerShot;

	std::string m_name;

	float m_bulletDamage;
	float m_bulletSpeed;

	int m_frameCounter = 0;
};

#endif  //WEAPON_H