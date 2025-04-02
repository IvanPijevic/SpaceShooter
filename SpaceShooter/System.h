#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#define NOMINMAX
#include <Windows.h>
#include <algorithm>

#include "Window.h"
#include "Input.h"
#include "Agent.h"
#include "Player.h"
#include "Timing.h"
#include "Bullet.h"

enum class GameState
{
	MAIN_MENU, PLAY, LEVEL_EDITOR, OPTIONS, PAUSE, QUIT
};

class System
{
public:
	System();

	void initGame();
	void processInput(float deltaTime);
	void gameLoop();
	void draw();
	void run();

	void updateBullets();

//public:
//	void drawPlayer();

private:
	GameState m_gameState;
	Window m_window;
	Input m_input;
	FpsLimiter m_fpsLimiter;

	Player m_player;
	Position m_playerPosition;

	//Timing
	const int m_desiredFPS;
	const float m_maxDeltaTime;
	const int m_maxPhysicsSteps;

	//fps
	float m_maxFPS;
	float m_fps;
	float m_time;

	std::vector<Bullet> m_bullets;  //On screen
};

#endif  //SYSTEM_H