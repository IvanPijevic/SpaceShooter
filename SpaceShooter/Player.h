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

	float m_speed = 10.0f;
	float m_verticalSpeed = 12.0f;
	float m_horizontalSpeed = 30.0f;

	int m_currentGunIndex = 0;

	short m_lives = 3;

	//deps for update
	//**
	short m_screenWidth = 0;
	short m_screenHeight = 0;
	Input* m_input = nullptr;
	std::vector<Bullet>* m_bullets = nullptr;
	//**

	Draw m_draw;

	Position m_startPosition = Position{4, 13 /*28*/};
};

#endif  //PLAYER_H