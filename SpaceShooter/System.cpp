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
	HANDLE handleInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inputRecord;
	DWORD eventsRead;
	bool evnt = true;

	while (evnt)
	{
		ReadConsoleInput(handleInput, &inputRecord, 1, &eventsRead);

		switch (inputRecord.EventType)
		{
		case KEY_EVENT:
			m_input.pressKey(inputRecord.Event.KeyEvent.bKeyDown);
			std::cout << "KEYKEY" << std::endl;
			break;
		}
	}

	//if (m_input.isKeyDown())
	//{
	//	std::cout << "W key" << std::endl;
	//}
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
