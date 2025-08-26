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


class Enemy : public Agent
{
public:
	Enemy();
	~Enemy() = default;

	void update(float deltaTime) override;
	void draw(Size windowSize, std::vector<CHAR_INFO>& buffer) override;
	void init();
	void getScreenSize(short screenWidth, short screenHeight);

	void addWaveToBuffer();

	const std::vector<LevelData>& getLevelData() const;
	const std::vector<LevelData>& getCurrentWave() const;

private:
	Direction m_direction;
	Position m_position;
	Draw m_draw;

	std::unique_ptr<Level> m_level;

	std::vector<LevelData> m_lvlData;
	std::vector<LevelData> m_currentWaveData;

	short m_screenWidth;
	short m_screenHeight;

	int m_currentWave;
	bool m_isWaveDead;
};

#endif  //ENEMY_H