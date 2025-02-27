#pragma once


#include <iostream>

class Player
{
public:
	Player();
	~Player();

	/*void init(short positionX, short positionY, wchar_t ch, WORD attributes);*/
	void draw(short x, short y);

	wchar_t* getPlayerShape() { return &m_playerShape[0][0]; }
	short getHeight() { return m_height; }
	short getWidth() { return m_width; }

private:
	static constexpr short m_width = 3;
	static constexpr short m_height = 2;

	wchar_t m_playerShape[m_height][m_width];
};

