#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>

enum class GameState
{
	MAIN_MENU, PLAY, GAME_EDITOR, OPTIONS, PAUSE, QUIT
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

};

#endif  //SYSTEM_H