#include "Player.h"

Player::Player() :
	m_playerShape{ {L' ', L'A', L' '}, {L'T', L'X', L'T'} },
	m_startPosition(58,27),
	m_speed(20.0f)
{}

Player::~Player()
{ }

void Player::init(Position position, float speed, Input* input)
{
	m_position = position;
	m_speed = speed;
	m_input = input;
}

void Player::update(short screenWidth, short screenHeight, float deltaTime)
{
	if (m_input->isKeyDown('A'))
	{
		m_position.x -= m_speed * deltaTime;
	}

	if (m_input->isKeyDown('D'))
	{
		m_position.x += m_speed * deltaTime;
	}
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