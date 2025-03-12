#include "System.h"

System::System() :
	m_gameState(GameState::PLAY),
	m_window(128, 64),  // == 1024x768
	m_player(Position(58, 27))
{}

void System::initGame()
{
	m_playerPosition = m_player.getPosition();

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

			if (m_input.isKeyPressed('W')) 
			{
				m_playerPosition.y -= 1;
				m_player.setPosition(m_playerPosition);
			}
			if (m_input.isKeyPressed('A')) 
			{
				m_playerPosition.x -= 1;
				m_player.setPosition(m_playerPosition);
			}
			if (m_input.isKeyPressed('S')) 
			{
				m_playerPosition.y += 1;
				m_player.setPosition(m_playerPosition);
			}
			if (m_input.isKeyPressed('D')) 
			{
				m_playerPosition.x += 1;
				m_player.setPosition(m_playerPosition);
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

	m_player.draw(m_window.getWindowSize(), m_window.getBuffer());

	m_window.Draw();
	Sleep(33);
}

void System::run()
{
	initGame();
	gameLoop();
}