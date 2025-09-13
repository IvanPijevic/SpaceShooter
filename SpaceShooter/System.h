#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#define NOMINMAX
#include <Windows.h>
#include <algorithm>
#include <functional>

#include "Window.h"
#include "Input.h"
#include "Agent.h"
#include "Player.h"
#include "Enemy.h"
#include "Timing.h"
#include "Bullet.h"
#include "Stats.h"

enum class GameState
{
	MAIN_MENU, PLAY, LEVEL_EDITOR, OPTIONS, PAUSE, QUIT
};

class System
{
public:
	void initGame();
	void processInput(float deltaTime);
	void gameLoop();
	void draw();
	void run();

	void updateBullets();

private:
	GameState m_gameState = GameState::PLAY;
	Window m_window = Window(128,32);
	Input m_input;
	FpsLimiter m_fpsLimiter;

	Player m_player;
	Enemy m_enemy;
	Stats m_stats;

	//Timing
	const int m_desiredFPS = 60;
	const float m_maxDeltaTime = 1.0f;
	const int m_maxPhysicsSteps = 6;

	//fps
	float m_maxFPS = 60.0f;
	float m_fps;
	float m_time = 0.0f;

	std::vector<Bullet> m_bullets;  //On screen
	std::vector<std::unique_ptr<Enemy>> m_enemiesToDraw;
};

#endif  //SYSTEM_H