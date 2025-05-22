#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "Input.h"
#include "DataStructures.h"
#include "Agent.h"
#include "Bullet.h"
#include "Weapon.h"

class Player : public Agent<3,2>
{
public:
	Player();
	~Player();
	
	void addWeapon(Weapon* weapon);
	void init(Position position, float m_speed);
	void update(Input& input, short screenWidth, short screenHeight, float deltaTime, std::vector<Bullet>& bullets );
	void draw(Size windowSize, std::vector<CHAR_INFO>& buffer) override;

	//TODO check is player in window borders
	//Logic
	void limitToScreen(short screenWidth, short screenHeight);


	wchar_t* getPlayerShape() { return &m_shipShape[0][0]; }
	short getHeight() { return m_height; }
	short getWidth() { return m_width; }

	//Getter
	Position getPosition() { return m_position; }
	Position getStartPosition() { return m_startPosition; }

	//Setter
	void setPosition(Position pos) { m_position = pos; }

private:

	std::vector<Weapon*> m_weapons;

	float m_speed;

	int m_currentGunIndex;

	Draw m_draw;

	Position m_startPosition;
};

#endif  //PLAYER_H