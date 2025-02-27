#include "Player.h"

Player::Player() :
	m_playerShape{ {L' ', L'A', L' '}, {L'T', L'X', L'T'} }
{}

Player::~Player()
{ }

void Player::draw(short x, short y)
{
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			std::wcout << j;
		}
		std::wcout << std::endl;
	}
}