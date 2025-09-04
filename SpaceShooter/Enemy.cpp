#include "Enemy.h"

Enemy::Enemy() :
    Agent(2, 2),
    m_direction{ -1, 0 },
    m_screenWidth(0),
    m_screenHeight(0),
    m_currentWave(0),
    m_isWaveDead(true),
    m_cikCakCounter(0),
	m_shipsDestroyed(0)

{ 
    //Get level data
    m_level = std::make_unique<Level>();
    m_level->init("Levels/Level.txt");

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

void Enemy::addWaveToBuffer(std::vector<std::unique_ptr<Enemy>>& enemy)
{
    if (m_isWaveDead && m_currentWave < static_cast<int>(m_lvlData.size()))
    {
        if (!enemy.empty())
        {
            return;
        }

        short shipInterspace = 7; //Ship spacing
        Position position = { static_cast<float>(m_screenWidth + 3), 5 };

        //Randomize y position
        short randomNumber = getRandomNumber(5, 27);

        //Set positions
        if (m_lvlData[m_currentWave].trajectory == TRAJECTORY::LINE)
        {
            position.y = randomNumber;
        }

        //Add ships
        for (int i = 0; i < m_lvlData[m_currentWave].numberOfShips; i++)
        {
            auto newEnemy = std::make_unique<Enemy>();
            newEnemy->initEnemy(position, m_lvlData, m_currentWave);
            enemy.push_back(std::move(newEnemy));

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

void Enemy::isEnemyOnScreen(std::vector<std::unique_ptr<Enemy>>& enemy)
{
    for (int i = 0; i < enemy.size();)
    {
        if (enemy[i]->m_position.x + 3 <= 0)
        {
            enemy[i] = std::move(enemy.back());
            enemy.pop_back();
        }
        else
        {
            ++i;
        }
    }

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