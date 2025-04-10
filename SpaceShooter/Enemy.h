#ifndef ENEMY_H
#define ENEMY_H

#include "Agent.h"
#include "DataStructures.h"

#include <Vector>

class Enemy : Agent<3,2>
{
public:
	Enemy(Position position);
	~Enemy();

	void update();
	void draw();
	void init();

private:
	Position m_position;
	Direction m_direction;

	std::vector<WaveData> m_waveData;
};

#endif  //ENEMY_H