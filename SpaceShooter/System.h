#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <Windows.h>

#include "Window.h"
#include "Input.h"
#include "Agent.h"
#include "Player.h"

enum class GameState
{
	MAIN_MENU, PLAY, LEVEL_EDITOR, OPTIONS, PAUSE, QUIT
};

class System
{
public:
	System();

	void initGame();
	void processInput();
	void gameLoop();
	void draw();
	void run();

//public:
//	void drawPlayer();

private:
	GameState m_gameState;
	Window m_window;
	Input m_input;

	Player m_player;
	Position m_playerPosition;

};

#endif  //SYSTEM_H