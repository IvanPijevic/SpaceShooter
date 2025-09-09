#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>

class Level
{
public:
	Level();
	~Level();

	void init(const std::string& fileName);

	int getNumberOfWaves() const { return m_numberOfWaves; }

	std::vector<std::string>& getLevelData() { return m_levelData; }

private:
	std::vector<std::string> m_levelData;

	short m_numberOfWaves;
	short m_numberOfShipsInWave;
	float m_shipSpeed;
	std::string m_enemyType;
};

#endif  //LEVEL_H