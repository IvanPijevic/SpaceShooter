#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <Windows.h>	

#include "Window.h"

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

private:
	GameState m_gameState;
	Window m_window;
};

#endif  //SYSTEM_H