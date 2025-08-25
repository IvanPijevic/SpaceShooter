#ifndef ENEMY_H
#define ENEMY_H

#include "Agent.h"
#include "DataStructures.h"
#include "Level.h"

#include <sstream>
#include <string>
#include <iostream>
#include <Vector>
#include <memory>

//Enemy spec
enum class TRAJECTORY
{
	LINE, DOUBLE_LINE, CIKCAK
};

enum class ENEMY_TYPE
{
	DRONE, BATTLE_SHIP
};

struct LevelData
{
	int numberOfShips;
	ENEMY_TYPE enemyType;
	TRAJECTORY trajectory;
};

class Enemy : public Agent
{
public:
	Enemy(Position position);
	~Enemy() = default;

	void update(float deltaTime) override;
	void draw(Size windowSize, std::vector<CHAR_INFO>& buffer) override;
	void init();

private:
	Direction m_direction;
	Draw m_draw;

	std::unique_ptr<Level> m_level;

	std::vector<LevelData> m_lvlData;
};

#endif  //ENEMY_H