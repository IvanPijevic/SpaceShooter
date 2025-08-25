#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::init(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open()) 
	{
		std::cerr << "Failed to open file: " << fileName << std::endl;
		std::exit(1);
	}

	std::string line;

	while (std::getline(file, line))
	{
		if (line.empty() || line[0] == '#')
		{
			continue;
		}

		m_levelData.push_back(line);
	}
	file.close();
}