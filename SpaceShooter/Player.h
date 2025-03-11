#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "Agent.h"

class Player : public Agent
{
public:
	Player(short positionX, short positionY);
	~Player();
	
	/*void init(short positionX, short positionY, wchar_t ch, WORD attributes);*/
	void draw(Size windowSize, std::vector<CHAR_INFO>& buffer) override;

	wchar_t* getPlayerShape() { return &m_playerShape[0][0]; }
	short getHeight() { return m_height; }
	short getWidth() { return m_width; }

private:
	static constexpr short m_width = 3;
	static constexpr short m_height = 2;

	wchar_t m_playerShape[m_height][m_width];

	Draw m_drawPixel;
	
	short m_posX;
	short m_posY;
};

#endif  //PLAYER_H