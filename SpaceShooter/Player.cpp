#include "Player.h"

Player::Player() :
	m_playerShape{ {L' ', L'A', L' '}, {L'T', L'X', L'T'} },
	m_startPosition(60, 60),
	m_currentGunIndex(-1)  //No weapon
{}

Player::~Player()
{ }

void Player::addWeapon(Weapon* weapon)
{
	m_weapons.push_back(weapon);

	if (m_currentGunIndex == -1)
	{
		m_currentGunIndex = 0;
	}
}

void Player::init(Position position, float speed)
{
	m_position = position;
	m_speed = speed;
}

void Player::update(Input& input, short screenWidth, short screenHeight, float deltaTime, std::vector<Bullet>& bullets)
{
	if (input.isKeyPressed('W'))
	{
		m_position.y -= 1;
	}

	if (input.isKeyPressed('S'))
	{
		m_position.y += 1;
	}

	if (input.isKeyPressed('A'))
	{
		m_position.x -= 1;
	}

	if (input.isKeyPressed('D'))
	{
		m_position.x += 1;
	}

	//TODO weapon change
	if (input.isKeyPressed('Q') && m_weapons.size() >= 0)
	{
		m_currentGunIndex = 0;
	}
	else if (input.isKeyPressed('E') && m_weapons.size() >= 1)
	{
		m_currentGunIndex = 1;
	}


	//if (input.isKeyPressed(VK_SPACE) && m_weapons.size() >= 0)
	//{
		//Default weapon
		if (m_currentGunIndex != -1)
		{
			Position bulletPosition;  //max broj metaka TODO
			bulletPosition = m_position;
			bulletPosition.x += 1;
			bulletPosition.y -= 1;

			Direction dir = { 0, -1 };

			m_weapons[m_currentGunIndex]->update(input.isKeyPressed(VK_SPACE), bulletPosition, dir, bullets);
			/*m_weapons[m_weaponNumber]->update(input.isKeyPressed(VK_SPACE), bulletPosition[0], dir, *m_bullets, deltaTime);*/
		}
	//}

}

void Player::draw(Size windowSize, std::vector<CHAR_INFO>& buffer)
{
	wchar_t* shape = &m_playerShape[0][0];

	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			wchar_t ch = shape[i * m_width + j];
			m_draw.drawPixel(m_position.x + j, m_position.y + i, ch, FOREGROUND_RED | FOREGROUND_INTENSITY,
				windowSize, buffer);
		}
	}
}