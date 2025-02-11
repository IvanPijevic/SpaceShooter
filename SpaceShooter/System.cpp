#include "System.h"

System::System() :
	m_gameState(GameState::PLAY),
	m_window(128, 64)  // == 1024x768 ?
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
	m_window.Clear();



	m_window.Draw();

}

void System::run()
{
	initGame();
	gameLoop();
}
