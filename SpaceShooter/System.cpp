#include "System.h"

System::System() :
	m_gameState(GameState::PLAY),
	m_window(128, 32),  //width / height 
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
	m_player.init(m_player.getStartPosition(), 1.0f, m_window.getWindowSize().width, m_window.getWindowSize().height);
	m_player.setInputAndBullets(m_input, m_bullets);
	m_player.addWeapon(std::make_unique<Weapon>("Basic laser", 7, 1, 10.0f, 2.0f));
	m_player.addWeapon(std::make_unique<Weapon>("Basic laser", 30, 1, 10.0f, 1.0f));
	m_enemy.init();
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
			
			m_player.update(deltaTime);
			m_enemy.update(deltaTime);
			//m_player.limitToScreen(m_window.getWindowSize().width, m_window.getWindowSize().height);
			
			updateBullets();

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

	m_player.draw(m_window.getWindowSize(), m_window.getBuffer());
	m_enemy.draw(m_window.getWindowSize(), m_window.getBuffer());

	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i].draw(m_window.getWindowSize(), m_window.getBuffer());
	}

	m_window.Draw();
}

void System::run()
{
	initGame();
	gameLoop();
}

void System::updateBullets()
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i].update();
	}
}