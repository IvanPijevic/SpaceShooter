#include "System.h"

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
			for (auto& enemy : m_enemiesToDraw)
			{
				enemy.update(deltaTime);
			}
			//End game if all waves are done
			if(m_enemy.isWaveDead() && m_enemy.getMaxWaves() == m_enemy.getCurrentWave())
			{
				m_gameState = GameState::QUIT;
			}

			//Check collision Enemy - Player
			std::for_each(m_enemiesToDraw.begin(), m_enemiesToDraw.end(), [this](Enemy& enemy)
				{
					if (m_player.colideWithEnemy(enemy))
					{
						m_player.setLives(m_player.getLives() - 1);
						m_stats.setLives(m_player.getLives());

						if (m_player.getLives() <= 0)
						{
							m_gameState = GameState::QUIT;
						}

						m_player.setPosition(m_player.getStartPosition());
					}
				});

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
	for (Enemy& enemy : m_enemiesToDraw)
	{
		enemy.draw(m_window.getWindowSize(), m_window.getBuffer());
	}

	//Draw bullets
	for (Bullet& bullet : m_bullets)
	{
		bullet.draw(m_window.getWindowSize(), m_window.getBuffer());
	}

	//Draw stats
	m_stats.draw(m_window.getBuffer(), m_window.getWindowSize());

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
	std::vector<Bullet>::iterator it = m_bullets.begin();
	while (it != m_bullets.end())
	{
		it->update();
		if (it->getLifeTime() <= 0)
			it = m_bullets.erase(it);
		else
			++it;
	}

	//Check collision bullet - enemy
	std::vector<Enemy>::iterator enemyIt = m_enemiesToDraw.begin();
	while (enemyIt != m_enemiesToDraw.end())
	{
		std::vector<Bullet>::iterator bulletIt = m_bullets.begin();
		while (bulletIt != m_bullets.end())
		{
			if (bulletIt->colideWithAgent(*enemyIt))
			{
				// Reduce health points
				enemyIt->setHealthPoints(enemyIt->getHealthPoints() - bulletIt->getDamage());

				// Delete bullet
				bulletIt = m_bullets.erase(bulletIt);

				if (enemyIt->getHealthPoints() <= 0)
				{
					// Update destroyed ships
					m_enemy.setShipsDestroyed(m_enemy.getShipsDestroyed() + 1);

					// Update score
					m_stats.setScore(m_stats.getScore() + 7);

					// Delete enemy
					enemyIt = m_enemiesToDraw.erase(enemyIt);
					break;
				}
				else
				{
					continue;
				}
			}
			else
			{
				++bulletIt;
			}
		}

		if (enemyIt != m_enemiesToDraw.end())
			++enemyIt;
	}
}