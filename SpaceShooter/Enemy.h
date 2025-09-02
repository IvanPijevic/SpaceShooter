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
#include <random>


class Enemy : public Agent
{
public:
	Enemy();
	~Enemy() = default;

	void initEnemy(const Position& position, const std::vector<LevelData>& waveData, int currentWave);
	void update(float deltaTime) override;
	void draw(Size windowSize, std::vector<CHAR_INFO>& buffer) override;
	void init();
	void getScreenSize(short screenWidth, short screenHeight);

	void addWaveToBuffer(std::vector<std::unique_ptr<Enemy>>& enemy);

	const std::vector<LevelData>& getLevelData() const;

	void isEnemyOnScreen(std::vector<std::unique_ptr<Enemy>>& enemy);

	//TODO move somewhere else
	int getRandomNumber(int min, int max);

	void setShipsDestroyed(int ships) { m_shipsDestroyed = ships; }
	int getShipsDestroyed() const { return m_shipsDestroyed; }	

	//Unit tests
	const std::vector<std::vector<wchar_t>>& getShipShape() const;
	bool isWaveDead() const;

private:
	Direction m_direction;
	Draw m_draw;

	std::unique_ptr<Level> m_level;

	std::vector<LevelData> m_lvlData;

	std::vector<std::vector<wchar_t>> m_shipShape;
	

	short m_screenWidth;
	short m_screenHeight;
	short m_cikCakCounter;

	int m_currentWave;
	int m_shipsDestroyed;

	bool m_isWaveDead;
};

#endif  //ENEMY_H