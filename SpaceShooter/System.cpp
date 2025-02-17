#include "System.h"

System::System() :
	m_gameState(GameState::PLAY),
	m_window(128, 64)  // == 1024x768 ?
{

}

void System::initGame()
{
	SDL_Init(SDL_INIT_EVENTS);
}

void System::processInput()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case SDL_EVENT_QUIT:
				m_gameState = GameState::QUIT;
				break;

			case SDL_EVENT_KEY_DOWN:
				m_input.pressKey(evnt.key.key);
				break;

			case SDL_EVENT_KEY_UP:
				m_input.releaseKey(evnt.key.key);
				break;
		}
	}

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
