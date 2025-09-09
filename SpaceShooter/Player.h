#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include <memory>

#include "Input.h"
#include "DataStructures.h"
#include "Agent.h"
#include "Bullet.h"
#include "Weapon.h"

class Player : public Agent
{
public:
	Player();
	~Player();
	
	void addWeapon(std::unique_ptr<Weapon> weapon);
	void init(Position position, float speed, short screenWidth, short screenHeight);
	void setInputAndBullets(Input& input, std::vector<Bullet>& bullets);
	void update(float deltaTime) override;
	void draw(Size windowSize, std::vector<CHAR_INFO>& buffer) override;

	//Logic
	void limitToScreen();
	bool colideWithEnemy(const Agent& agent);

	//Set/get
	wchar_t* getPlayerShape() { return &m_shipShape[0][0]; }
	short getHeight() const { return m_height; }
	short getWidth() const { return m_width; }
	Position getStartPosition() const { return m_startPosition; }
	short getLives() const { return m_lives; }
	void setLives(short lives) { m_lives = lives; }
	void setPosition(Position position) { m_position = position; }

private:

	std::vector<std::unique_ptr<Weapon>> m_weapons;

	float m_speed;
	float m_verticalSpeed;
	float m_horizontalSpeed;

	int m_currentGunIndex;

	short m_lives;

	//deps for update
	//**
	short m_screenWidth;
	short m_screenHeight;
	Input* m_input;
	std::vector<Bullet>* m_bullets;
	//**

	Draw m_draw;

	Position m_startPosition;
};

#endif  //PLAYER_H