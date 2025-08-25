#include "Enemy.h"

Enemy::Enemy(Position position): 
    Agent(2, 2),
    m_direction{ -1, 0 }

{ 
    setPosition(position);

    // Initialize simple enemy shape
    m_shipShape[0][0] = L'<';
    m_shipShape[0][1] = L'o';
    m_shipShape[1][0] = L' ';
    m_shipShape[1][1] = L'-';

    //Get level data
    m_level = std::make_unique<Level>();
    m_level->init("Levels/Level.txt");

}

void Enemy::init() 
{
    std::vector<std::string> levelData = m_level->getLevelData();
    m_lvlData.clear();

    for (size_t i = 0; i < levelData.size(); i += 3) 
    {
        LevelData wave;

        //Get Number of ships in wave
        std::istringstream iss(levelData[i]);
        std::string temp;
        iss >> temp >> wave.numberOfShips;

        //Get Enemy typerr
        iss.clear();
        iss.str(levelData[i + 1]);
        std::string enemyTypeStr;
        iss >> temp >> enemyTypeStr;

        if (enemyTypeStr == "DRONE") 
        {
            wave.enemyType = ENEMY_TYPE::DRONE;
        }
        if (enemyTypeStr == "BATTLE_SHIP") 
        {
            wave.enemyType = ENEMY_TYPE::BATTLE_SHIP;
        }

        //Get trajectory
        iss.clear();
        iss.str(levelData[i + 2]);
        std::string trajectoryStr;
        iss >> temp >> trajectoryStr;

        if (trajectoryStr == "LINE") 
        {
            wave.trajectory = TRAJECTORY::LINE;
        }
        if (trajectoryStr == "DOUBLE_LINE") 
        {
            wave.trajectory = TRAJECTORY::DOUBLE_LINE;
        }
        if (trajectoryStr == "CIKCAK") 
        {
            wave.trajectory = TRAJECTORY::CIKCAK;
        }


        m_lvlData.push_back(wave);
    }

}

void Enemy::update(float deltaTime) 
{
    m_position.x += m_direction.x * 5.0f * deltaTime;
    m_position.y += m_direction.y * 5.0f * deltaTime;
}

void Enemy::draw(Size windowSize, std::vector<CHAR_INFO>& buffer) 
{
    for (int i = 0; i < m_height; i++) 
    {
        for (int j = 0; j < m_width; j++) 
        {
            int x = static_cast<int>(m_position.x + j);
            int y = static_cast<int>(m_position.y + i);
            if (x >= 0 && x < windowSize.width && y >= 0 && y < windowSize.height) 
            {
                wchar_t ch = m_shipShape[i][j];
                m_draw.drawPixel(x, y, ch, FOREGROUND_GREEN | FOREGROUND_INTENSITY, windowSize, buffer);
            }
        }
    }
}
