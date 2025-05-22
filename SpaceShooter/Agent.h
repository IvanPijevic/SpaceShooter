#ifndef AGENT_H
#define AGENT_H

#include "DataStructures.h"
#include "Draw.h"

#include <vector>

template <short width, short height>

class Agent
{
public:
	Agent();
	virtual ~Agent();

	void init();
	virtual void draw(Size windowSize, std::vector<CHAR_INFO>& buffer) = 0;


protected:
	static constexpr short m_width = width;
	static constexpr short m_height = height;
	wchar_t m_shipShape[m_height][m_width];

	int m_hp;
	int m_shield;
	int m_energy;

	Position m_position;
};

template <short width, short height>
Agent<width, height>::Agent()
{
	m_hp = 100;
	m_shield = 0;
	m_energy = 50;
	m_position = { 0, 0 };

	for (short i = 0; i < m_height; ++i) 
	{
		for (short j = 0; j < m_width; ++j) 
		{
			m_shipShape[i][j] = L' '; // Default shape
		}
	}
}

template <short width, short height>
Agent<width, height>::~Agent()
{
	
}

template <short width, short height>
void Agent<width, height>::init()
{

}

#endif  //AGENT_H