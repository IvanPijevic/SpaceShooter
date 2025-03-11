#include "Player.h"

Player::Player(short positionX, short positionY) :
	m_playerShape{ {L' ', L'A', L' '}, {L'T', L'X', L'T'} },
	m_posX(positionX),
	m_posY(positionY)
{}

Player::~Player()
{ }

void Player::draw(Size windowSize, std::vector<CHAR_INFO>& buffer)
{
	wchar_t* shape = &m_playerShape[0][0];

	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			wchar_t ch = shape[i * m_width + j];
			m_drawPixel.drawPixel(m_posX + j, m_posY + i, ch, FOREGROUND_RED | FOREGROUND_INTENSITY,
				windowSize, buffer);
		}
	}
}