#include "Player.h"

Player::Player() : 
	Agent(2,3),
	m_startPosition(4, 13 /*28*/),
	m_currentGunIndex(-1),  //No weapon
	m_speed(10.0f),  //orginalno 500 i 1000
	m_screenWidth(0),
	m_screenHeight(0),
	m_input(nullptr),
	m_bullets(nullptr),
	m_verticalSpeed(12.0f),
	m_horizontalSpeed(30.0f),
	m_lives(3)

{
	m_shipShape[0][0] = L'-';
	m_shipShape[0][1] = L' ';
	m_shipShape[1][0] = L'o';
	m_shipShape[1][1] = L'>';
	m_shipShape[2][0] = L'-';
	m_shipShape[2][1] = L' ';
}

Player::~Player()
{ }

void Player::addWeapon(std::unique_ptr<Weapon> weapon)
{
	m_weapons.push_back(std::move(weapon));

	if (m_currentGunIndex == -1 && !m_weapons.empty()) 
	{
		m_currentGunIndex = 0;
	}
}

void Player::init(Position position, float speed, short screenWidth, short screenHeight)
{
	m_position = position;
	m_speed = speed;
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
}

void Player::setInputAndBullets(Input& input, std::vector<Bullet>& bullets) 
{
	m_input = &input;
	m_bullets = &bullets;
}

void Player::update(float deltaTime)
{
	if (!m_input || !m_bullets) return;

	if (m_input->isKeyPressed('W'))
	{
		m_position.y -= m_speed * m_verticalSpeed * deltaTime;
	}

	if (m_input->isKeyPressed('S'))
	{
		m_position.y += m_speed * m_verticalSpeed * deltaTime;
	}

	if (m_input->isKeyPressed('A'))
	{
		m_position.x -= m_speed * m_horizontalSpeed * deltaTime;
	}

	if (m_input->isKeyPressed('D'))
	{
		m_position.x += m_speed * m_horizontalSpeed * deltaTime;
	}

	//Weapon switching and firing
	if (m_input->isKeyPressed('Q') && !m_weapons.empty())
	{
		m_currentGunIndex = 0;
	}
	else if (m_input->isKeyPressed('E') && m_weapons.size() > 1)
	{
		m_currentGunIndex = 1;
	}

	if (m_input->isKeyPressed(VK_SPACE) && m_currentGunIndex != -1 && m_currentGunIndex < m_weapons.size())
	{
		Position bulletPosition = m_position;
		bulletPosition.x += m_width;
		bulletPosition.y += m_height / 2;
		Direction dir = { 1, 0 };
		m_weapons[m_currentGunIndex]->update(true, bulletPosition, dir, *m_bullets);
	}

	limitToScreen();
}

void Player::draw(Size windowSize, std::vector<CHAR_INFO>& buffer)
{
	for (int i = 0; i < m_height; i++) 
	{
		for (int j = 0; j < m_width; j++) 
		{
			int x = static_cast<int>(m_position.x + j);
			int y = static_cast<int>(m_position.y + i);
			if (x >= 0 && x < windowSize.width && y >= 0 && y < windowSize.height) 
			{
				wchar_t ch = m_shipShape[i][j];
				m_draw.drawPixel(x, y, ch, FOREGROUND_RED | FOREGROUND_INTENSITY, windowSize, buffer);
			}
		}
	}
}

void Player::limitToScreen()
{
	if (m_position.x > m_screenWidth - 25) 
	{
		m_position.x = m_screenWidth - 25;
	}
	if (m_position.x < 2) 
	{
		m_position.x = 2;
	}
	if (m_position.y > m_screenHeight - 5) 
	{
		m_position.y = m_screenHeight - 5;
	}
	if (m_position.y < 0) 
	{
		m_position.y = 0;
	}
}

bool Player::colideWithEnemy(const Agent& agent)
{
	Position enemyPosition = agent.getPosition();
	short enemyWidth = agent.getWidth();
	short enemyHeight = agent.getHeight();

	if (m_position.x < enemyPosition.x + enemyWidth && m_position.x + enemyWidth > enemyPosition.x
		&& m_position.y < enemyPosition.y + enemyHeight && m_position.y + enemyHeight > enemyPosition.y)
	{
		return true;
	}

	return false;
}