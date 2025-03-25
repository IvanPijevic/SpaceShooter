#ifndef AGENT_H
#define AGENT_H

#include "DataStructures.h"
#include "Draw.h"

class Agent
{
public:
	Agent();
	virtual ~Agent();

	void init();
	virtual void draw(Size windowSize, std::vector<CHAR_INFO>& buffer) = 0;

protected:
	int m_hp;
	int m_shield;
	int m_energy;


	Position m_position;
};

#endif  //AGENT_H