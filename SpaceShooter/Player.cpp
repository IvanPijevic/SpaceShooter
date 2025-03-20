#include "Player.h"

Player::Player(Position pos) :
	m_playerShape{ {L' ', L'A', L' '}, {L'T', L'X', L'T'} },
	Agent(Position(58,27))
{}

Player::~Player()
{ }

void Player::update(Input& input, short screenWidth, short screenHeight, float deltaTime)
{

}

void Player::draw(Size windowSize, std::vector<CHAR_INFO>& buffer)
{
	wchar_t* shape = &m_playerShape[0][0];

	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			wchar_t ch = shape[i * m_width + j];
			m_drawPixel.drawPixel(m_position.x + j, m_position.y + i, ch, FOREGROUND_RED | FOREGROUND_INTENSITY,
				windowSize, buffer);
		}
	}
}