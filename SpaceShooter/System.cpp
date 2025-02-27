#include "System.h"

System::System() :
	m_gameState(GameState::PLAY),
	m_window(128, 64),  // == 1024x768
	m_x(58),
	m_y(27)
{

}

void System::initGame()
{
	
}

void System::processInput()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inputRecord;
	DWORD eventRead;

		ReadConsoleInput(hInput, &inputRecord, 1, &eventRead);
		{
			if (inputRecord.EventType == KEY_EVENT) 
			{
				const KEY_EVENT_RECORD& keyEvent = inputRecord.Event.KeyEvent;
				if (keyEvent.bKeyDown) 
				{
					m_input.pressKey(keyEvent.wVirtualKeyCode);
				}
				else 
				{
					m_input.releaseKey(keyEvent.wVirtualKeyCode);
				}

				if (keyEvent.wVirtualKeyCode == VK_ESCAPE) 
				{
					m_gameState = GameState::QUIT;
				}
			}

			if (m_input.isKeyPressed('W')) {
				m_y -= 1;
			}
			if (m_input.isKeyPressed('A')) {
				m_x -= 1;
			}
			if (m_input.isKeyPressed('S')) {
				m_y += 1;
			}
			if (m_input.isKeyPressed('D')) {
				m_x += 1;
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

	//m_window.SetPixel(m_x, m_y, L'X', FOREGROUND_RED | FOREGROUND_INTENSITY);

	drawPlayer();

	m_window.Draw();
	Sleep(33);
}

void System::run()
{
	initGame();
	gameLoop();
}


void System::drawPlayer()
{
	wchar_t* shape = m_player.getPlayerShape();
	short height = m_player.getHeight();
	short width = m_player.getWidth();

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			wchar_t ch = shape[i * width + j];
			m_window.SetPixel(m_x + j, m_y + i, ch, FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
}