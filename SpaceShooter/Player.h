#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "Input.h"
#include "DataStructures.h"
#include "Agent.h"

class Player : public Agent
{
public:
	Player();
	~Player();
	
	void init(Position position, float m_speed);
	void update(Input& input, short screenWidth, short screenHeight, float deltaTime);
	void draw(Size windowSize, std::vector<CHAR_INFO>& buffer) override;

	wchar_t* getPlayerShape() { return &m_playerShape[0][0]; }
	short getHeight() { return m_height; }
	short getWidth() { return m_width; }

	//Getter
	Position getPosition() { return m_position; }
	Position getStartPosition() { return m_startPosition; }

	//Setter
	void setPosition(Position pos) { m_position = pos; }

private:
	static constexpr short m_width = 3;
	static constexpr short m_height = 2;

	float m_speed;

	wchar_t m_playerShape[m_height][m_width];

	Draw m_drawPixel;

	Position m_startPosition;
};

#endif  //PLAYER_H