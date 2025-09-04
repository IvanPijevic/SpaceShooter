#include "Agent.h"

Agent::Agent(short width, short height) :
	m_width(width),
	m_height(height),
	m_hp(DEFAULT_HP),
	m_shield(0),
	m_energy(DEFAULT_ENERGY),
	m_position{ 0,0 },
	m_speed(0.0f)

{
	m_shipShape.resize(height, std::vector<wchar_t>(width, L' '));
}

void Agent::takeDamage(float damage)
{
	if (m_shield >= damage)
	{
		m_shield -= damage;
	}
	else
	{
		damage -= m_shield;
		m_shield = 0;
		m_hp -= damage;

		if (m_hp < 0)
		{
			m_hp = 0;
		}
	}
}