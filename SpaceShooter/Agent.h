#ifndef AGENT_H
#define AGENT_H

#include "DataStructures.h"
#include "Draw.h"

#include <vector>

class Agent
{
public:
	Agent(short width, short height);
	virtual ~Agent() = default;

	virtual void update(float deltaTime) = 0;
	virtual void draw(Size windowSize, std::vector<CHAR_INFO>& buffer) = 0;

	bool isAlive() const { return m_hp > 0.0f; }
	void takeDamage(float damage);

	//Get/set
	Position getPosition() const {return m_position; }
	void setPosition(Position position) { m_position = position; }
	short getWidth() const { return m_width; }
	short getHeight() const { return m_height; }
	float getHealthPoints() const { return m_hp; }
	void setHealthPoints(float hp) { m_hp = hp; }


protected:
	std::vector<std::vector<wchar_t>> m_shipShape;

	short m_width;
	short m_height;

	float m_hp;
	float m_shield;
	float m_energy;

	float m_speed;

	Position m_position;

	static constexpr float DEFAULT_HP = 30.0f;
	static constexpr float DEFAULT_ENERGY = 50.0f;

};

#endif  //AGENT_H