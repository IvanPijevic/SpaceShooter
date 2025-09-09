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
	m_player.addWeapon(std::make_unique<Weapon>("Second laser", 30, 1, 30.0f, 1.0f));
	m_enemy.init();
	m_enemy.getScreenSize(m_window.getWindowSize().width, m_window.getWindowSize().height);
}

void System::processInput(float deltaTime)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inputRecord;
	DWORD eventRead;

	DWORD numEvents = 0;
	GetNumberOfConsoleInputEvents(hInput, &numEvents);

	if (numEvents > 0)
	{
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

			//Update enemy - bullets collision, lifetime...
			updateBullets();

			//Update enemy
			m_enemy.addWaveToBuffer(m_enemiesToDraw);
			for (int i = 0; i < m_enemiesToDraw.size(); i++)
			{
				m_enemiesToDraw[i]->update(deltaTime);
			}

			//Check collision Enemy - Player
			for(int i = 0; i < m_enemiesToDraw.size(); i++)
			{
				if (m_player.colideWithEnemy(*m_enemiesToDraw[i]))
				{
					m_player.setLives(m_player.getLives() - 1);

					//Check player lives
					if(m_player.getLives() <= 0)
					{ 
						m_gameState = GameState::QUIT;
					}

					m_player.setPosition(m_player.getStartPosition());

				}
			}

			m_enemy.isEnemyOnScreen(m_enemiesToDraw);

			totalDeltaTime -= deltaTime;
			i++;
		}

	draw();

	m_fps = m_fpsLimiter.end();
	}

}

void System::draw()
{
	m_window.Clear();

	//Draw player
	m_player.draw(m_window.getWindowSize(), m_window.getBuffer());

	//Draw enemy ships
	for (int i = 0; i < m_enemiesToDraw.size(); i++)
	{
		m_enemiesToDraw[i]->draw(m_window.getWindowSize(), m_window.getBuffer());
	}

	//Draw bullets
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

	//Update bullets, remove old
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i].update();

		if (m_bullets[i].getLifeTime() <= 0)
		{
			m_bullets[i] = std::move(m_bullets.back());
			m_bullets.pop_back();
		}
	}

	//Check collision bullet - enemy

	for (int i = 0; i < m_enemiesToDraw.size(); i++)
	{
		for (int j = 0; j < m_bullets.size(); j++)
		{
			if (m_bullets[j].colideWithAgent(*m_enemiesToDraw[i]))
			{
				//Reduce health points
				m_enemiesToDraw[i]->setHealthPoints(m_enemiesToDraw[i]->getHealthPoints() - m_bullets[j].getDamage());

				//Delete bullet
				m_bullets[j] = std::move(m_bullets.back());
				m_bullets.pop_back();

				if (m_enemiesToDraw[i]->getHealthPoints() <= 0)
				{
					//Update destroyed ships
					m_enemy.setShipsDestroyed(m_enemy.getShipsDestroyed() + 1);

					//Delete enemy ship from vector
					m_enemiesToDraw[i] = std::move(m_enemiesToDraw.back());
					m_enemiesToDraw.pop_back();
				}
			}
		}
	}
}