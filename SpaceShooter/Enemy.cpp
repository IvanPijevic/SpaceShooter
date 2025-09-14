#include "Enemy.h"

Enemy::Enemy() :
    Agent(2, 2)
{ 
    m_level.init("Levels/Level.txt");

    //Enemy speed
    m_speed = 15.0f;

}

void Enemy::initEnemy(const Position& position, const std::vector<LevelData>& waveData, int currentWave)
{
    m_position = position;
    ENEMY_TYPE type = waveData[currentWave].enemyType;

    //Ship shape by type
    if (type == ENEMY_TYPE::DRONE)
    {
        m_width = 1;
        m_height = 1;
        m_shipShape = std::vector<std::vector<wchar_t>>(m_height, std::vector<wchar_t>(m_width, L'O'));
    }
}

void Enemy::init() 
{
    const std::vector<std::string>& levelData = m_level.getLevelData();
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

        //Get trajectory
        iss.clear();
        iss.str(levelData[i + 2]);
        std::string trajectoryStr;
        iss >> temp >> trajectoryStr;

        if (trajectoryStr == "LINE") 
        {
            wave.trajectory = TRAJECTORY::LINE;
        }

        m_lvlData.push_back(wave);
    }

}

void Enemy::getScreenSize(short screenWidth, short screenHeight)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
}

void Enemy::update(float deltaTime) 
{
    //Move left for everything
    m_position.x += m_direction.x * m_speed * deltaTime;
}

void Enemy::draw(Size windowSize, std::vector<CHAR_INFO>& buffer) 
{
    int yOffset = 0;
    for (auto& row : m_shipShape)
    {
        int xOffset = 0;
        for (auto& ch : row)
        {
            int x = static_cast<int>(m_position.x + xOffset);
            int y = static_cast<int>(m_position.y + yOffset);
            if (x >= 0 && x < windowSize.width && y >= 0 && y < windowSize.height)
            {
                m_draw.drawPixel(x, y, ch, FOREGROUND_GREEN | FOREGROUND_INTENSITY, windowSize, buffer);
            }
            ++xOffset;
        }
        ++yOffset;
    }
}

void Enemy::addWaveToBuffer(std::vector<Enemy>& enemy)
{
    if (m_isWaveDead && m_currentWave < static_cast<int>(m_lvlData.size()))
    {
		m_maxWaves = static_cast<int>(m_lvlData.size());

        if (!enemy.empty())
        {
            return;
        }

        short shipInterspace = 7; //Ship spacing
        Position position = { static_cast<float>(m_screenWidth + 3), 5 };

        //Randomize y position
        short randomNumber = getRandomNumber(7, 27);

        //Set positions
        if (m_lvlData[m_currentWave].trajectory == TRAJECTORY::LINE)
        {
            position.y = randomNumber;
        }

        //Add ships
        for (int i = 0; i < m_lvlData[m_currentWave].numberOfShips; i++)
        {
			Enemy newEnemy;
            newEnemy.initEnemy(position, m_lvlData, m_currentWave);
            enemy.push_back(newEnemy);

            if (m_lvlData[m_currentWave].trajectory == TRAJECTORY::LINE)
            {
                position.x += shipInterspace;
            }
        }

        m_currentWave++;
        m_isWaveDead = false;
    }
}


const std::vector<LevelData>& Enemy::getLevelData() const
{
    return m_lvlData;
}

void Enemy::isEnemyOnScreen(std::vector<Enemy>& enemy)
{
    enemy.erase(std::remove_if(enemy.begin(), enemy.end(),[](const auto& e) 
        { 
            return e.m_position.x + 3 <= 0; 
        }),enemy.end());

    if (enemy.empty())
    {
        m_isWaveDead = true;
    }
}

int Enemy::getRandomNumber(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

const std::vector<std::vector<wchar_t>>& Enemy::getShipShape() const
{
    return m_shipShape;
}

bool Enemy::isWaveDead() const
{
    return m_isWaveDead;
}