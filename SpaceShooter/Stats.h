#ifndef STATS_H
#define STATS_H

#include <vector>
#include <iostream>	
#include <string>	
#include <Windows.h>	
#include "DataStructures.h"	
#include "Draw.h"	


class Stats
{
public:
		void init();
		void update(float deltaTime);
		void draw(std::vector<CHAR_INFO>& buffer, Size windowSize);
		void setScore(int score) { m_score = score; }
		int getScore() const { return m_score; }
		void setLevel(int level) { m_level = level; }
		int getLevel() const { return m_level; }
		void setLives(int lives) { m_lives = lives; }
		int getLives() const { return m_lives; }	

private:
		int m_score = 0;
		int m_level = 1;
		int m_lives = 3;
		
		Draw m_draw;	
};

#endif // !STATS_H