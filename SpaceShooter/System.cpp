#include "System.h"

System::System() :
	m_gameState(GameState::PLAY)
{

}

void System::initGame()
{

}

void System::processInput()
{

}

void System::gameLoop()
{
	while (m_gameState != GameState::QUIT)
	{
		processInput();
		draw();
	}

}

void System::draw()
{

}

void System::run()
{
	initGame();
	gameLoop();
}
