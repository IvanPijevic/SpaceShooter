#include "System.h"

System::System() :
	m_gameState(GameState::PLAY),
	m_window(128, 64),  // == 1024x768
	m_desiredFPS(60),
	m_maxDeltaTime(1.0f),
	m_maxPhysicsSteps(6),
	m_maxFPS(60.0f),
	m_time(0.0f)

{
}

void System::initGame()
{
	m_fpsLimiter.setMaxFPS(m_maxFPS);

}

void System::processInput(float deltaTime)
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

			
			if (m_input.isKeyPressed('A')) 
			{
				m_playerPosition.x -= 1;
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
	Timing timer(m_desiredFPS);

	while (m_gameState != GameState::QUIT)
	{
		m_fpsLimiter.begin();

		float totalDeltaTime = timer.getDeltaTime();

		int i = 0;
		while (totalDeltaTime > 0.0f && i < m_maxPhysicsSteps)
		{
			float deltaTime = std::min(totalDeltaTime, m_maxDeltaTime);

			//Update game
			processInput(deltaTime);
			m_player.update(m_input, m_window.getWindowSize().width, m_window.getWindowSize().height, deltaTime);


			totalDeltaTime -= deltaTime;
			i++;
		}

	//static int frameCounter = 0;
	//frameCounter++;
	//if (frameCounter == 10)
	//{
	//	std::cout << m_fps;
	//	frameCounter = 0;
	//}

	draw();

	m_fps = m_fpsLimiter.end();
	}

}

void System::draw()
{
	m_window.Clear();

	//m_window.SetPixel(m_x, m_y, L'X', FOREGROUND_RED | FOREGROUND_INTENSITY);

	m_player.draw(m_window.getWindowSize(), m_window.getBuffer());

	m_window.Draw();
	/*Sleep(33);*/
}

void System::run()
{
	initGame();
	gameLoop();
}